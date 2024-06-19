/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:06:14 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/14 07:33:36 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**command_path(char *cmd, t_struct **rr)
{
	char	*path;
	char	**dir;

	path = get_env("PATH", rr);
	if (!path)
		return (NULL);
	(void)cmd;
	dir = ft_split(path, ':');
	return (dir);
}

int	init_command_search(char *cmd, t_struct **rr, char **path)
{
	if (cmd[0] == '\0')
		return (0);
	*path = get_env("PATH", rr);
	if (!*path)
	{
		if (access(cmd, X_OK) == -1 && ft_strncmp(cmd, "export", 6) != 0)
		{
			printf("minishell: %s: No such file or directory\n", cmd);
			return (0);
		}
		*path = "\0";
	}
	return (1);
}

int	setup_search_structures(char *path, char *cmd, char ***dir, char ***arg)
{
	*dir = ft_split(path, ':');
	if (!*dir)
		return (0);
	if (cmd[0] == ' ')
	{
		free_tab((void **)*dir);
		free(cmd);
		printf("%s: command not found\n", cmd);
		return (0);
	}
	*arg = ft_split(cmd, ' ');
	if (!*arg)
		return (0);
	return (1);
}

void	exist_path(int *exist, int *i, char **arg, char **dir)
{
	char	*full_path;
	char	*cmd_path;

	full_path = ft_strjoin(dir[*i], "/");
	cmd_path = ft_strjoin(full_path, arg[0]);
	if (access(cmd_path, X_OK) == 0)
		*exist = 1;
	free(full_path);
	free(cmd_path);
	*i += 1;
}

int	process_command_search(char **dir, char **arg, t_struct **rr)
{
	int	exist;
	int	i;

	exist = 0;
	if (ft_strncmp(arg[0], "export", 6) == 0
		|| ft_strncmp(arg[0], "env", 3) == 0
		|| ft_strncmp(arg[0], "echo", 4) == 0
		|| ft_strncmp(arg[0], "unset", 6) == 0)
		return (1);
	if (!arg[0] || arg[0][0] == ' ')
		return (0);
	if (arg[0][0] == '/')
		return (1);
	if (arg[0][0] != '.' && arg[0][1] != '/')
	{
		i = 0;
		while (dir[i] && !exist)
			exist_path(&exist, &i, arg, dir);
		if (!exist || arg[0][0] == ' ')
		{
			(*rr)->interro = 127;
			free((*rr)->lun);
			(*rr)->lun = NULL;
			printf("%s: command not found\n", arg[0]);
		}
	}
	else
		exist = 1;
	return (exist);
}
