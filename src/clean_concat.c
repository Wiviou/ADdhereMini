/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_concat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:05:55 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:10:31 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	redir_clean(char **ss, int i, int *f, char *s)
{
	if (i != 0)
	{
		if (!ft_isspace(s[i - 1]) && s[i - 1] != '>')
		{
			(*ss)[*f] = ' ';
			*f += 1;
		}
	}
	(*ss)[*f] = s[i];
	if (s[i + 1] != '\0')
	{
		if (!ft_isspace(s[i + 1]) && s[i + 1] != '>')
		{
			*f += 1;
			(*ss)[*f] = ' ';
		}
	}
}

static void	redir_1clean(char **ss, int i, int *f, char *s)
{
	if (i != 0)
	{
		if (!ft_isspace(s[i - 1]))
		{
			(*ss)[*f] = ' ';
			*f += 1;
		}
	}
	(*ss)[*f] = s[i];
	if (s[i + 1] != '\0')
	{
		if (!ft_isspace(s[i + 1]))
		{
			*f += 1;
			(*ss)[*f] = ' ';
		}
	}
}

static void	wredir_clean(char **ss, int *i, int *f, char *s)
{
	if (s[*i] == '|' || s[*i] == '>' || s[*i] == '<')
	{
		if (s[*i] == '>')
			redir_clean(ss, *i, f, s);
		else if (s[*i] == '|')
			redir_1clean(ss, *i, f, s);
		else if (s[*i] == '<')
			redir_1clean(ss, *i, f, s);
		*i += 1;
		*f += 1;
	}
	else
	{
		(*ss)[*f] = s[*i];
		*f += 1;
		*i += 1;
	}
}

char	*clean_concat(char *s)
{
	int		i;
	int		v;
	int		f;
	char	*ss;

	i = 0;
	v = 0;
	f = 0;
	ss = NULL;
	if (!s || !*s)
		return (NULL);
	while (s[i])
		so_clean(s, &i, &v);
	ss = malloc(sizeof(char) * (ft_strlen(s) + v + 1));
	if (!ss)
		return (NULL);
	i = 0;
	while (s[i])
		wredir_clean(&ss, &i, &f, s);
	ss[f] = '\0';
	free(s);
	return (ss);
}
