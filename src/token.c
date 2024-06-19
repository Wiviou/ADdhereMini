/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 01:34:39 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 23:33:57 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_in(char *in, t_struct **rr)
{
	if (ft_strncmp(in, "cd", 2) == 0)
	{
		(*rr)->is_cd = 1;
		return (1);
	}
	
	if (ft_strncmp(in, "unset", 5) == 0)
		return (1);
	
	return (0);
}

int	tokennix01(t_struct **rr, char **t)
{
	if (!*t)
		return (1);
	if (ft_strncmp(*t, "|", 1) == 0)
	{
		(*rr)->state.fff = 1;
		(*rr)->is_cd = 0;
		return (2);
	}
	return (0);
}

void	plop(char c, int *hh)
{
	printf("minishell: syntax error near unexpected token '%c'\n", c);
	*hh = 0;
}

int	tokennix02(char **t, t_struct **rr, int *hh)
{
	if (ft_strncmp(*t, "<", 1) == 0)
	{
		if (*hh)
		{
			plop('<', hh);
			return (3);
		}
		*hh = 1;
		(*rr)->state.fff = 0;
		return (1);
	}
	else if (ft_strncmp(*t, ">", 1) == 0 && (*t)[1] == '\0')
	{
		if (*hh)
		{
			plop('>', hh);
			return (3);
		}
		*hh = 1;
		(*rr)->state.fff = 0;
		return (2);
	}
	return (0);
}

int	tokennix03(t_struct **rr, char **t, int *hh)
{
	if (ft_strncmp(*t, ">>", 2) == 0)
	{
		if (*hh)
		{
			printf("minishell: syntax error near unexpected token '>>'\n");
			*hh = 0;
			return (3);
		}
		*hh = 1;
		(*rr)->state.fff = 0;
		return (1);
	}
	else if (built_in(*t, rr))
	{
		*hh = 0;
		(*rr)->state.fff = 0;
		return (2);
	}
	*hh = 0;
	return (0);
}
