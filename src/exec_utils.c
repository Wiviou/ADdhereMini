/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 01:07:48 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:10:16 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"




void	pero_ft(char *s, void *k)
{
	int	fd;

	free(k);
	printf("minishell: %s: No such file or directory\n", s);
	fd = open(".interro.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
	ft_putnbr_fd(1, fd);
	close(fd);
	exit(EXIT_FAILURE);
}

void	is_in_file(t_stat *state)
{
	state->in = open(state->sss, O_RDONLY);
	if (dup2(state->in, STDIN_FILENO) == -1)
		pero_ft(state->sss, (char *)state->cmd_path);
	close(state->in);
	if (state->sss)
		free(state->sss);
}

void	is_out_redir(t_stat *state)
{
	destroy_file();
	state->in_fd = open(".temp.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	ft_get_line(state->pip[0], state->in_fd);
	close(state->pip[0]);
	close(state->in_fd);
}

