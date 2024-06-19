/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_now2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:20:55 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:03:08 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	part1(t_stat *state, char **cmd)
{
	if (access(cmd[0], X_OK) == 0)
		state->cmd_path = ft_strdup(cmd[0]);
}

static void	part2(t_stat *state, char **cmd, t_envp **envp, t_struct **rr)
{
	(*rr)->interro = 0;

	state->y++;
	state->pid = fork();
	if (state->pid == -1)
		pero_frexit("fork", (char *)state->cmd_path);
	if (state->pid == 0)
	{
		close(state->piper[state->x * 2]);
		close(state->piper[(state->x - 1) * 2 + 1]);
		if (dup2(state->piper[state->x * 2 + 1], STDOUT_FILENO) == -1)
			pero_frexit("dup2", (char *)state->cmd_path);
		if (dup2(state->piper[(state->x - 1) * 2], STDIN_FILENO) == -1)
			pero_frexit("open", (char *)state->cmd_path);
		close(state->piper[(state->x - 1) * 2]);
		close(state->piper[state->x * 2 + 1]);
		exec_sig(state, cmd, envp, rr);
	}
}

static void	part3(t_stat *state)
{
	state->vg--;
	close(state->piper[(state->x - 1) * 2 + 1]);
	close(state->piper[(state->x - 1) * 2]);
	if (state->cmd_path)
	{
		free(state->cmd_path);
		state->cmd_path = NULL;
	}
	state->pide[state->y] = state->pid;
	state->is_in = 1;
}

/* ************************************************************************** */

void	command_exec_now2(char **cmd, t_envp **envp, t_struct **rr)
{
	part1(&(*rr)->state, cmd);
	part2(&(*rr)->state, cmd, envp, rr);
	part3(&(*rr)->state);
}