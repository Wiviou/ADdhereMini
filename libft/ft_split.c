/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:13:40 by Jean Ruhlma       #+#    #+#             */
/*   Updated: 2024/06/13 10:46:58 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static char	**free_mem(char **tab, size_t id)
{
	while (id)
		free(tab[--id]);
	free(tab);
	return (NULL);
}

static char	**add_to(char **tab, const char *s, size_t st, size_t ln)
{
	size_t	id;

	id = 0;
	while (tab[id])
		id++;
	tab[id] = ft_substr(s, st, ln);
	if (!tab[id])
		return (free_mem(tab, id));
	return (tab);
}

static char	**ft_fill(char **tab, const char *s, char c)
{
	size_t	start;
	size_t	len;
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
		{
			start = i;
			len = 0;
			while (s[i] && s[i] != c)
			{
				len++;
				i++;
			}
			tab = add_to(tab, s, start, len);
			if (!tab)
				return (NULL);
		}
		else
			i++;
	}
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	i;
	size_t	count;

	if (!s)
		return (NULL);
	i = 0;
	count = ft_count(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (i <= count)
		tab[i++] = NULL;
	if (!ft_fill(tab, s, c))
		return (NULL);
	return (tab);
}
