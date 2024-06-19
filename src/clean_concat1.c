/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_concat1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:11:21 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:11:24 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	v_clean(char *s, int i, int *v)
{
	if (i != 0)
	{
		if (!ft_isspace(s[i - 1]))
		{
			*v += 1;
		}
	}
	if (s[i + 1] != '\0')
	{
		if (!ft_isspace(s[i + 1]))
		{
			*v += 1;
		}
	}
}

static void	i_clean(char *s, int i, int *v)
{
	if (i != 0)
	{
		if (!ft_isspace(s[i - 1]) && s[i - 1] != '>')
		{
			*v += 1;
		}
	}
	if (s[i + 1] != '\0')
	{
		if (!ft_isspace(s[i + 1]) && s[i + 1] != '>')
		{
			*v += 1;
		}
	}
}

void	so_clean(char *s, int *i, int *v)
{
	if (s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
	{
		if (s[*i] == '>')
			i_clean(s, *i, v);
		else if (s[*i] == '|')
			v_clean(s, *i, v);
		else if (s[*i] == '<')
			v_clean(s, *i, v);
	}
	*i += 1;
}
