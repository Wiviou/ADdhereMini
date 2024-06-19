/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:18:48 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/14 07:35:34 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_t	*init_k(void)
{
	t_t	*k_;

	k_ = malloc(sizeof(t_t));
	if (!k_)
		return (NULL);
	k_->envp = NULL;
	k_->node = NULL;
	k_->sub = NULL;
	k_->catn = NULL;
	k_->rr = NULL;
	if (check_struct(&k_->rr, &k_->catn))
		return (NULL);
	k_->rr->enve = malloc(sizeof(char *) * 256);
	if (!k_->rr->enve)
	{
		free(k_->rr);
		free(k_->catn);
		return (NULL);
	}
	return (k_);
}

int	main_read(t_t **k_, char **line, char ***dir, char **luna)
{
	char	*invite;
	int		inf;

	init_main_read(k_);
	*dir = NULL;
	invite = NULL;
	(*k_)->rr->lun = NULL;
	invite = invite_pwd(&(*k_)->rr);
	*luna = readline(invite);
	if (*luna != NULL)
	{
		*line = ft_strdup(*luna);
		(*k_)->rr->lun = *line;
		free(*luna);
	}
	free(invite);
	if (!*luna)
	{
		free(*luna);
		printf("exit\n");
		return (1);
	}
	
	inf = 0;
	while ((*line)[inf] != '\0' && ft_isspace((*line)[inf]))
		inf++;
	if (**line == '\0' || (*line)[inf] == '\0')
	{
		free(*line);
		return (7);
	}
	add_history(*line);
	return (0);
}

int	pr_clean(char ***dir, t_t **k_, char **processed_line)
{
	delete_list_and(&(*k_)->node);
	free_tab((void **)(*dir));
	destroy_file();
	free(*processed_line);
	return (7);
}

int	p_main(char ***dir, t_t **k_, char **processed_line)
{
	t_node	*temp;

	token(*dir, &(*k_)->node, &(*k_)->sub, &(*k_)->rr);
	free(*processed_line);
	temp = (*k_)->node;
	while (temp != NULL)
	{
		if (temp->sub->dta->token == DEAD)
			(*k_)->rr->dead = 1;
		temp = temp->next;
	}
	if ((*k_)->rr->dead)
	{
		if ((*k_)->rr->state.piper != NULL)
			free((*k_)->rr->state.piper);
		if ((*k_)->rr->state.pide != NULL)
			free((*k_)->rr->state.pide);
		delete_list_and(&(*k_)->node);
		free_tab((void **)*dir);
		destroy_file();
		return (7);
	}
	return (1);
}
