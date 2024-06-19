/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:19:29 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:05:33 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_chr(char **s, t_struct **rr)
{
	int	lo;

	if (((*s)[0] == '/' && (*s)[1] != '\0' && !(*rr)->is_cd) || ((*s)[0] == '.'
			&& (*s)[1] == '.' && (*s)[2] == '/' && (*s)[3] != '\0'))
	{
		lo = is_inchr(s, rr);
		if (lo != 0)
			return (lo);
	}
	else if (((*s)[0] == '/' && (*s)[1] == '\0' && !(*rr)->is_cd)
		|| ((*s)[0] == '.' && (*s)[1] == '.' && (*s)[2] == '/'
			&& (*s)[3] == '\0' && !(*rr)->is_cd))
		return (2);
	return (0);
}

static int	r_ask(char *s, char *bu)
{
	size_t	l;

	l = ft_strlen(bu);
	if (ft_strncmp(s, bu, l) == 0)
		return (1);
	return (0);
}

int	valid_path(char **s, char **dir, t_struct **rr)
{
	int		result;
	char	*full_path;
	int		i;
	char	*cmdd;

	result = 0;
	i = 0;
	if (r_ask(*s, "pwd") || r_ask(*s, "echo")
		|| r_ask(*s, "env") || r_ask(*s, "export")
		|| r_ask(*s, "unset"))
		return (1);
	while (dir[i])
	{
		full_path = ft_strjoin(dir[i], "/");
		cmdd = ft_strjoin(full_path, *s);
		free(full_path);
		if (access(cmdd, X_OK) == 0)
		{
			change_last_access(cmdd, rr);
			result = 1;
		}
		free(cmdd);
		if (result)
			break ;
		i++;
	}
	return (result);
}

int	valid_access(char **s, t_struct **rr)
{
	int		lo;
	char	*path;
	char	**dir;
	int		result;
	int		i;

	is_chr(s, rr);
	lo = is_chr(s, rr);
	if (lo != 0)
		return (lo);
	path = get_env("PATH", rr);
	if (!path)
		return (0);
	dir = ft_split(path, ':');
	result = valid_path(s, dir, rr);
	i = 0;
	while (dir[i])
		free(dir[i++]);
	free(dir);
	return (result);
}
