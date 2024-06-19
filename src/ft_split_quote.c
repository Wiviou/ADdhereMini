/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:22:44 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 23:03:23 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/libft.h"

static int	is_separator(char ch, char c1, char c2)
{
	return (ch == c1 || ch == c2);
}

// Counts the number of segments in the string considering two separators
static size_t	ft_count(const char *s, char c1, char c2)
{
	int		in;
	int		inn;
	size_t	count;
	size_t	i;

	in = 0;
	inn = 0;
	count = 0;
	i = 0;
	if (!is_separator(s[0], c1, c2))
	{
		count = 1;
	}
	while (s[i])
	{
		is_in_quote(s[i], &in, &inn);
		if (is_separator(s[i], c1, c2) && !in && !inn && s[i + 1] != '\0'
			&& !is_separator(s[i + 1], c1, c2))
		{
			count++;
		}
		i++;
	}
	return (count);
}

// Adds a new string segment to the array of strings
static char	**add_to(char **tab, const char *s, size_t st, size_t ln)
{
	size_t	id;

	id = 0;
	while (tab[id])
	{
		id++;
	}
	tab[id] = ft_substr(s, st, ln);
	if (!tab[id])
	{
		return (free_mem(tab, id)); // Assumes implementation of free_mem
	}
	return (tab);
}

// Handles a single segment of the string that should be added to the result
static char	**handle_segment(char **tab, const char *s, char c1, char c2,
		size_t *i)
{
	size_t	start;
	size_t	len;
	int		in;
	int		inn;

	start = *i;
	len = 0;
	in = 0;
	inn = 0;
	while (s[*i] && (!is_separator(s[*i], c1, c2) || in || inn))
	{
		is_in_quote(s[*i], &in, &inn);
		len++;
		(*i)++;
	}
	if (len > 0)
	{
		tab = add_to(tab, s, start, len);
		if (!tab)
		{
			return (NULL);
		}
	}
	return (tab);
}

// Fills the result array with segments from the string
static char	**ft_fill(char **tab, const char *s, char c1, char c2)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((i == 0 || is_separator(s[i - 1], c1, c2)) && !is_separator(s[i],
				c1, c2))
		{
			tab = handle_segment(tab, s, c1, c2, &i);
			if (!tab)
			{
				return (NULL);
			}
		}
		else
		{
			i++;
		}
	}
	return (tab);
}

// Main function to split a string respecting quotes and two separators
char	**ft_split_quote(const char *s, char c1, char c2)
{
	char	**tab;
	size_t	i;
	size_t	count;

	i = 0;
	if (!s)
	{
		return (NULL);
	}
	count = ft_count(s, c1, c2);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
	{
		return (NULL);
	}
	while (i <= count)
	{
		tab[i++] = NULL;
	}
	if (!ft_fill(tab, s, c1, c2))
	{
		return (NULL);
	}
	return (tab);
}
