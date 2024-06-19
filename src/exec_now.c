/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_now.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:00:12 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:09:07 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	part1(t_stat *state, char **cmd, t_struct **rr)
{
	(*rr)->interro = 0;
	if (access(cmd[0], X_OK) == 0)
	{
		state->cmd_path = ft_strdup(cmd[0]);
	}
}

static void	part2(t_stat *state, char **cmd, t_envp **envp, t_struct **rr)
{
	
	state->y++;
	state->pid = fork();
	if (state->pid == -1)
	{
		pero_frexit("fork", (char *)state->cmd_path);
	}
	if (state->pid == 0)
	{
		if (state->in_file)
			is_in_file(state);
		exec_sig(state, cmd, envp, rr);
	}
}

static void	part3(t_stat *state)
{
	int	status;

	waitpid(state->pid, &status, 0);
	if (state->in_file)
		state->in_file = 0;
	if (state->is_in_echo)
		state->is_in_echo = 0;
	state->vg--;
	state->pide[state->y] = state->pid;
	if (state->cmd_path)
	{
		free(state->cmd_path);
		state->cmd_path = NULL;
	}
	g_child_running = 1;
	setup_sigint_handler();
	if (state->is_redir)
		is_out_redir(state);
}

void	command_exec_now(char **cmd, t_envp **envp, t_struct **rr)
{
	part1(&(*rr)->state, cmd, rr);
	part2(&(*rr)->state, cmd, envp, rr);
	part3(&(*rr)->state);
}
