/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 01:06:42 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:29:51 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_child_running = 0;

void	perrus(char *s)
{
	int	fd;

	perror(s);
	fd = open(".interro.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
	ft_putnbr_fd(1, fd);
	close(fd);
	exit(EXIT_FAILURE);
}

void	part1(t_stat *state, char **cmd, t_struct **rr)
{
	if (cmd[0][0] != '/')
	{
		if (ft_strncmp(cmd[0], "export", 6) == 0)
			state->y++;
		if (path_exec(state, cmd, rr))
			return ;

	}
	else
		state->cmd_path = ft_strdup(cmd[0]);
	if (state->is_redir)
	{
		if (pipe(state->pip) == -1)
		{
			close(state->in_fd);
			pero_frexit("pipe", (char *)state->cmd_path);
		}
	}
	state->y++;
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
}

void	part2(t_stat *state, char **cmd, t_envp **envp, t_struct **rr)
{
		
	if (state->pid == 0)
	{
		if (state->is_redir)
		{
			
			if (dup2(state->pip[1], STDOUT_FILENO) == -1
				|| close(state->pip[0]) == -1 || close(state->pip[1]))
				pero_frexit("dup2", (char *)state->cmd_path);
		}
		if (state->in_file)
			is_in_file(state);
		exec_sig(state, cmd, envp, rr);
	}
}

void	part3(t_stat *state, char **cmd, t_envp **envp, t_struct **rr)
{
	
	if (state->in_file)
		state->in_file = 0;
	if (state->is_in_echo)
		state->is_in_echo = 0;
	if (ft_strncmp(cmd[0], "export", 6) == 0 && (cmd[1] != NULL || !state->is_redir))
	{
		if ((*rr)->lun != NULL) 
			free((*rr)->lun);
		(*rr)->lun = NULL;
		export_command(cmd, rr, envp);
	}
	if (ft_strncmp(cmd[0], "unset", 5) == 0)
	{
		delete_env(envp, cmd, rr);
	}
	state->vg--;
	state->pide[state->y] = state->pid;
	if (state->is_redir)
		close(state->pip[1]);
	if (state->cmd_path)
	{
		free(state->cmd_path);
		state->cmd_path = NULL;
	}
	g_child_running = 1;
	setup_sigint_handler();
	if (state->is_redir)
		is_out_redir(state);

	wait_pid(&state);
	
	
}

void	command_exec(char **cmd, t_envp **envp, t_struct **rr)
{
	part1(&(*rr)->state, cmd, rr);
	part2(&(*rr)->state, cmd, envp, rr);
	part3(&(*rr)->state, cmd, envp, rr);
	//interro_state(rr);
	sleep(0.9);
}
