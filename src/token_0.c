/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:19:29 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:13:08 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_token(t_token c)
{
	if (c == PIPE || c == COMMAND || c == REDIR_IN || c == REDIR_OUT
		|| c == APPEND_REDIR_OUT)
		return (1);
	return (0);
}

char	*get_env(char *key, t_struct **rr)
{
	size_t	len;
	int		i;

	if (key == NULL || rr == NULL || *rr == NULL || (*rr)->enve == NULL)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while ((*rr)->enve[i] != NULL)
	{
		if (ft_strncmp((*rr)->enve[i], key, len) == 0
			&& (*rr)->enve[i][len] == '=')
			return ((*rr)->enve[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	change_last_access(char *cmd, t_struct **rr)
{
	int	i;

	i = 0;
	while ((*rr)->enve[i])
	{
		if (ft_strncmp((*rr)->enve[i], "_=", 2) == 0)
		{
			free((*rr)->enve[i]);
			(*rr)->enve[i] = malloc(sizeof(char) * ft_strlen(cmd) + 3);
			if (!(*rr)->enve[i])
				return ;
			ft_strcpy((*rr)->enve[i], "_=");
			ft_strcat((*rr)->enve[i], cmd);
		}
		i++;
	}
}

int	is_innchr(char **s, struct stat *path_stat)
{
	if (stat(*s, path_stat) != -1)
	{
		if (S_ISCHR(path_stat->st_mode) || S_ISBLK(path_stat->st_mode))
			return (1);
		if (S_ISDIR(path_stat->st_mode))
			return (2);
	}
	return (0);
}

int	is_inchr(char **s, t_struct **rr)
{
	struct stat	path_stat;

	(*rr)->o = is_innchr(s, &path_stat);
	if ((*rr)->o != 0)
		return ((*rr)->o);
	if (access(*s, X_OK) == 0)
	{
		change_last_access(*s, rr);
		return (1);
	}
	else
	{
		if (stat(*s, &path_stat) != -1)
		{
			if (S_ISDIR(path_stat.st_mode))
				return (2);
			else
			{
				if (S_ISREG(path_stat.st_mode))
					return (0);
			}
		}
		else
			return (3);
	}
	return (0);
}
