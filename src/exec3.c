/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:20:55 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:29:48 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	part1(t_stat *state, char **cmd, t_struct **rr)
{
	if (cmd[0][0] != '/')
	{
		if (path_exec(state, cmd, rr))
			return ;
	}
	else
		state->cmd_path = ft_strdup(cmd[0]);
	if (state->is_redir)
	{
		if (pipe(state->pip) == -1)
			pero_frexit("pipe", (char *)state->cmd_path);
	}
}

static void	part2(t_stat *state, char **cmd, t_envp **envp, t_struct **rr)
{

	state->y++;
	if (ft_strncmp(cmd[0], "exit", 4) != 0)
	{
		state->pid = fork();
		if (state->pid == -1)
		{
			if (state->is_redir)
			{
				close(state->pip[0]);
				close(state->pip[1]);
			}
			pero_frexit("fork", (char *)state->cmd_path);
		}
		if (state->pid == 0)
		{
			if (state->is_redir)
			{
				close(state->pip[0]);
				if (dup2(state->pip[1], STDOUT_FILENO) == -1)
					pero_frexit("dup2", (char *)state->cmd_path);	
				close(state->pip[1]);
			}
			close(state->piper[(state->x - 1) * 2 + 1]);
			if (dup2(state->piper[(state->x - 1) * 2], STDIN_FILENO) == -1)
				pero_frexit("dup2", (char *)state->cmd_path);
			close(state->piper[(state->x - 1) * 2]);
			exec_sig(state, cmd, envp, rr);
		}
	}
}

static void	part3(t_stat *state, char **cmd)
{
	state->vg--;
	state->pide[state->y] = state->pid;
	close(state->piper[(state->x - 1) * 2 + 1]);
	close(state->piper[(state->x - 1) * 2]);
	if (state->is_redir)
		close(state->pip[1]);
	if (state->cmd_path)
	{
		free(state->cmd_path);
		state->cmd_path = NULL;
	}
	g_child_running = 1;
	setup_sigint_handler();
	if (ft_strncmp(cmd[0], "exit", 4) != 0)
	{
		if (state->is_redir)
			is_out_redir(state);
	}
	wait_pid(&state);
	state->is_in = 0;
}

void	command_exec3(char **cmd, t_envp **envp, t_struct **rr)
{
	part1(&(*rr)->state, cmd, rr);
	part2(&(*rr)->state, cmd, envp, rr);
	part3(&(*rr)->state, cmd);
	//interro_state(rr);
}

void	pero_frexit(char *s, void *k)
{
	int	fd;

	free(k);
	k = NULL;
	perror(s);
	fd = open(".interro.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
	ft_putnbr_fd(1, fd);
	close(fd);
	exit(EXIT_FAILURE);
}
