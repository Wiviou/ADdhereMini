/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 01:07:48 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:47:03 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	path_exec_1(char **full_path, char **dir, t_stat *state, char **cmd)
{
	char	*cmdd;
	int		i;

	cmdd = NULL;
	i = 0;
	while (dir[i])
	{
		free(*full_path);
		*full_path = ft_strjoin(dir[i], "/");
		cmdd = ft_strjoin(*full_path, cmd[0]);
		if (access(cmdd, X_OK) == 0)
		{
			state->cmd_path = ft_strdup(cmdd);
			free(cmdd);
			cmdd = NULL;
			break ;
		}
		free(cmdd);
		cmdd = NULL;
		i++;
	}
}

int	path_exec(t_stat *state, char **cmd, t_struct **rr)
{
	char	*path;
	char	**dir;
	char	*full_path;

	(*rr)->interro = 0;
	path = get_env("PATH", rr);
	if (!path)
	{
		return (1);
	}
	dir = ft_split(path, ':');
	if (!dir)
		return (1);
	full_path = NULL;
	path_exec_1(&full_path, dir, state, cmd);
	free(full_path);
	free_tab((void **)dir);
	return (0);
}
void	per_ft(char **s)
{
	int	fd;
	size_t	len = ft_strlen(*s) + 20 + 1;
	char 	*rew = malloc(sizeof(char) * (len));

	ft_strcpy(rew, *s);
	ft_strcat(rew, ": Command not found\n");
	write(1, rew, len  - 1);
	free(rew);
	fd = open(".interro.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
	ft_putnbr_fd(127, fd);
	close(fd);
	int	i = 0;
	while (s[i])
	{
		free(s[i++]);
		*s = NULL;
	}
	free(s);
	s = NULL;
}

static int	is_open(int fd)
{
	struct stat	buf;
	if (fstat(fd, &buf) != -1)
		return (1);
	else
		return (0);	
}

void	close_piper(t_stat *state, t_struct **rr)
{
	int	i = 0;
	while (i < (*rr)->nbr_pipe * 2)
	{
		if (is_open(state->piper[i]))
			close(state->piper[i]);
		i++;
	}
}

void	exec_sig(t_stat *state, char **cmd, t_envp **envp, t_struct **rr)
{
	struct sigaction	sa;


	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	close_piper(state, rr);
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
	{
		pwd_o(rr);
		free(state->cmd_path);
		state->cmd_path = NULL;
		free((*rr)->lun);
		(*rr)->lun = NULL;
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(cmd[0], "echo", 4) == 0)
	{
		ft_echo_co(cmd, rr);
		free(state->cmd_path);
		state->cmd_path = NULL;
		free((*rr)->lun);
		(*rr)->lun = NULL;
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
	{
		env_command(&(*rr)->envp);
		free(state->cmd_path);
		state->cmd_path = NULL;
		free((*rr)->lun);
		(*rr)->lun = NULL;
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(cmd[0], "export", 6) == 0 && cmd[1] == NULL && state->is_redir)
	{
		export_command(cmd, rr, envp);
		free(state->cmd_path);
		state->cmd_path = NULL;
		free((*rr)->lun);
		(*rr)->lun = NULL;
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(cmd[0], "export", 6) == 0 || ft_strncmp(cmd[0], "unset", 5) == 0)
	{
		free(state->cmd_path);
		state->cmd_path = NULL;
		exit(EXIT_FAILURE);
	}
	char	*truei = NULL;
	truei = ft_strdup(state->cmd_path);
	free(state->cmd_path);
	state->cmd_path = NULL;

	free((*rr)->lun);
	(*rr)->lun = NULL;
	if (execve(truei, cmd, (*rr)->eeenv) == -1)
		per_ft(cmd);
	free(rr);
	free(truei);
	exit(EXIT_FAILURE);
}
