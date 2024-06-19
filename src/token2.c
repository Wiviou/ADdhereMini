/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:00:51 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/17 23:34:09 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	tokennix04(t_struct **rr, char **t, int ret)
{
	if (ret == 2)
	{
		printf("minishell: %s: Is a directory\n", *t);
		(*rr)->interro = 126;
		return (2);
	}
	else if (ret == 3)
	{
		printf("minishell: %s: No such file or directory\n", *t);
		(*rr)->interro = 126;
		return (3);
	}
	else if (ret == 4)
	{
		printf("minishell: %s: Permission denied\n", *t);
		(*rr)->interro = 1;
		return (4);
	}
	return (0);
}

int	tokennix05(char **t, t_struct **rr)
{
	if (((*t)[0] == '.' && (*t)[1] == '/' && (*t)[2] == '\0') || ((*t)[0] == '.'
			&& (*t)[1] == '.' && (*t)[2] == '/' && (*t)[3] == '\0'
			&& !(*rr)->is_cd))
	{
		printf("minishell: %s: Is a directory\n", *t);
		return (1);
	}
	else if (((*t)[0] == '.' && (*t)[1] == '/' && (*t)[2] != '\0')
		|| ((*t)[0] == '.' && (*t)[1] == '.' && (*t)[2] == '/'
			&& (*t)[3] != '\0'))
	{
		if (access(*t, X_OK) != 0)
		{
			printf("minishell: %s: No such file or directory\n", *t);
			return (1);
		}
	}
	return (0);
}

int	tokennix06(t_struct **rr, char **t)
{
	int	ret;
	int	eyes;

	ret = valid_access(t, rr);
	if ((ret && (*t)[1] != '.') || ((*t)[0] == '.' && (*t)[1] == '/')
		|| (((*t)[0] == '.' && (*t)[1] == '.' && (*t)[2] == '/'
				&& !(*rr)->is_cd)) || ((*rr)->state.fff == 1 && !(*rr)->is_cd)|| (ret && !(*rr)->is_cd))
	{
		eyes = tokennix04(rr, t, ret);
		if (eyes == 2 || eyes == 3 || eyes == 4)
			return (1);
		else if ((*t)[0] == '.' && (*t)[1] == '/')
		{
			eyes = tokennix05(t, rr);
			if (eyes == 1)
				return (1);
		}
		(*rr)->state.fff = 0;
		return (4);
	}
	return (0);
}

t_token	tokennix07(char **t, t_struct **rr, int *hh)
{
	int	eyes;

	eyes = tokennix02(t, rr, hh);
	if (eyes == 1)
		return (REDIR_IN);
	else if (eyes == 2)
		return (REDIR_OUT);
	else if (eyes == 3)
		return (DEAD);
	eyes = tokennix03(rr, t, hh);
	if (eyes == 3)
		return (DEAD);
	else if (eyes == 1)
		return (APPEND_REDIR_OUT);
	else if (eyes == 2)
		return (BUILT_IN);
	return (R);
}

t_token	tokennix(char **t, t_struct **rr, int *hh)
{
	int		eyes;
	t_token	g;

	eyes = tokennix01(rr, t);
	if (eyes == 1)
		return (R);
	else if (eyes == 2)
		return (PIPE);
	g = tokennix07(t, rr, hh);
	if (g != R)
		return (g);
	eyes = tokennix06(rr, t);
	if (eyes == 1)
		return (DEAD);
	else if (eyes == 4)
		return (COMMAND);
	return (WORD);
}
