/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:56 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/13 09:03:59 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**extract_delimiters(char *line, int *num_delimiters)
{
	char	**delimiters;
	char	*start;
	int		capacity;
	char	*next_start;

	capacity = count_heredoc_delimiters(line);
	delimiters = (char **)malloc(capacity * sizeof(char *));
	if (!delimiters)
		return (NULL);
	start = line;
	*num_delimiters = 0;
	next_start = ft_strnstr(start, "<<", strlen(start));
	while (next_start)
	{
		start = next_start + 2;
		if (!extract_next_delimiter(&start, num_delimiters, delimiters,
				&capacity))
		{
			free_delimiters(delimiters, *num_delimiters);
			return (NULL);
		}
		next_start = ft_strnstr(start, "<<", strlen(start));
	}
	return (delimiters);
}

char	*extract_next_delimiter(char **start, int *num_delimiters,
		char **delimiters, int *capacity)
{
	char	*end;
	size_t	len;

	while (**start && ft_isspace(**start))
		(*start)++;
	end = *start;
	while (*end && !ft_isspace(*end))
		end++;
	len = end - *start;
	if (*num_delimiters >= *capacity)
	{
		if (!resize_delimiters_array(delimiters, capacity))
			return (NULL);
	}
	delimiters[*num_delimiters] = (char *)malloc(len + 1);
	if (!delimiters[*num_delimiters])
		return (NULL);
	ft_memcpy(delimiters[*num_delimiters], *start, len);
	delimiters[*num_delimiters][len] = '\0';
	(*num_delimiters)++;
	*start = end;
	return (*start);
}

char	**resize_delimiters_array(char **delimiters, int *capacity)
{
	int		new_capacity;
	char	**new_delimiters;
	int		i;

	new_capacity = *capacity * 2;
	new_delimiters = (char **)malloc(new_capacity * sizeof(char *));
	if (!new_delimiters)
		return (NULL);
	i = 0;
	while (i < *capacity)
	{
		new_delimiters[i] = delimiters[i];
		i++;
	}
	free(delimiters);
	*capacity = new_capacity;
	return (new_delimiters);
}

void	free_delimiters(char **delimiters, int num_delimiters)
{
	int	i;

	i = 0;
	while (i < num_delimiters)
	{
		free(delimiters[i]);
		i++;
	}
	free(delimiters);
}

void	cleanup_delimiters_and_tempfiles(char **delimiters,
		char **temp_filenames, int num_delimiters)
{
	int	i;

	i = 0;
	while (i < num_delimiters)
	{
		if (delimiters[i])
			free(delimiters[i]);
		if (temp_filenames && temp_filenames[i])
			free(temp_filenames[i]);
		i++;
	}
	free(delimiters);
	free(temp_filenames);
}
