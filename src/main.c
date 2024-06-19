/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:32:40 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 23:04:03 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_255(t_t **k_)
{
	int	fd;

	printf("minishell: exit: %s: numeric argument required\n",
			(*k_)->node->sub->next->dta->val);
	fd = open(".interro.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
	ft_putnbr_fd(255, fd);
	close(fd);
	interro_state(&(*k_)->rr);
	(*k_)->rr->exit_val = (*k_)->rr->interro;
}

int	p_man(char ***dir, t_t **k_, char **line)
{
	free((*k_)->rr->state.pide);
	free((*k_)->rr->state.piper);
	free_tab((void **)*dir);
	delete_envp(&(*k_)->envp);
	destroy_file();
	printf("exit\n");
	if ((*k_)->rr->exit_nodig)
		print_255(k_);
	delete_list_and(&(*k_)->node);
	if ((*k_)->rr->exit_to_many)
	{
		printf("minishell: exit: too many arguments\n");
		return (7);
	}
	free(*line);
	free_tab((void **)(*k_)->rr->enve);
	destroy_file();
	rl_clear_history();
	exit((*k_)->rr->exit_val);
	return (1);
}

int	man_main(char ***dir, t_t **k_, char **line, char **processed_line)
{
	if (*processed_line && **processed_line)
	{
		(*k_)->o = pro_main(k_, processed_line);
		if ((*k_)->o == 7)
			return (7);
		*dir = ft_split_quote(*processed_line, ' ', '\t');
		*dir = clean_quote_tab(*dir, &(*k_)->rr);
		(*k_)->o = p_main(dir, k_, processed_line);
		if ((*k_)->o == 7)
			return (7);
	}
	else
		free(*processed_line);
	int kio =  read_shell(&(*k_)->node, &(*k_)->envp, &(*k_)->rr, (*k_)->rr->enve);
	if (kio)
	{
		if (kio == 7)
			return (7);
		(*k_)->o = p_man(dir, k_, line);
		if ((*k_)->o == 7)
			return (7);
	}
	return (1);
}

int	v_main(char ***dir, t_t **k_, char **line)
{
	size_t	needed_length;
	char	*processed_line;
	int		o;

	if (ft_strnstr(*line, "<<", strlen(*line)))
		*line=process_heredocs(*line);	
	(*k_)->rr->ambigus = 0;
	needed_length = calculate_required_length(*line, &(*k_)->rr);
	processed_line = perform_replacements(*line, needed_length, &(*k_)->rr);
	o = man_main(dir, k_, line, &processed_line);
	if (o == 7)
		return (7);
	free(*line);
	if ((*k_)->rr->state.piper != NULL)
		free((*k_)->rr->state.piper);
	if ((*k_)->rr->state.pide != NULL)
		free((*k_)->rr->state.pide);
	if (*dir != NULL)
		free_tab((void **)*dir);
	*dir = NULL;
	
	return (1);
}

void	ma_main(char ***dir, t_t **k_, char **line, char **env)
{
	int	o;

	(*k_)->luna = NULL;
	init_main(&(*k_)->rr, &(*k_)->envp, env);
	(*k_)->rr->envp = (*k_)->envp;
	while (1)
	{
		
		o = main_read(k_, line, dir, &(*k_)->luna);
		if (o == 1)
			break ;
		else if (o == 7)
		{
			continue ;
		}
		*line = concat_n(*line, &(*k_)->catn);
		
		o = v_main(dir, k_, line);
		if (o == 7)
		{
			continue ;
		}
		if ((*k_)->rr->dead)
		{
			continue ;
		}
		
	}
	if ((*k_)->luna != NULL)
		free((*k_)->luna);
	free_tab((void **)(*k_)->rr->enve);
	if ((*k_)->rr != NULL)
		free((*k_)->rr);
	delete_envp(&(*k_)->envp);
	free((*k_)->luna);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	
	char	**dir;
	t_t		*k_;

	if (argc == 1 && argv[1] == NULL)
	{
	g_child_running = 0;
	setup_sigint_handler();
	using_history();
	k_ = init_k();
	if (!k_)
		return (1);
	line = NULL;
	dir = NULL;
	ma_main(&dir, &k_, &line, env);
	free(k_->luna);
	free(k_->catn);
	free(k_);
	destroy_file();
	rl_clear_history();
	}
	return (0);
}
