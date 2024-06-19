/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_multi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:22:10 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:05:27 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	update_quote_state(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
	{
		*in_single = !*in_single;
	}
	else if (c == '\"' && !(*in_single))
	{
		*in_double = !*in_double;
	}
}

static int	line_in_quote(const char *line)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (line[i])
	{
		update_quote_state(line[i], &in_single, &in_double);
		i++;
	}
	return (in_single || in_double);
}
/*
static char	*append_line(char *line, const char *r_line)
{
	size_t	lin;
	size_t	lrn;
	char	*new_line;

	lin = ft_strlen(line);
	lrn = ft_strlen(r_line);
	new_line = my_reallox(line, lin + lrn + 1, lin);
	if (!new_line)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	ft_strcpy(new_line + lin, r_line);
	return (new_line);
}
*/
/*static char	*read_and_process_line(char *line)
{
	char	*r_line;
	char	*temp_line;

	r_line = readline(">");
	if (!r_line)
		return (NULL);
	if (*r_line == '\0')
	{
		free(r_line);
		return (line);
	}
	temp_line = append_line(line, r_line);
	free(r_line);
	return (temp_line);
}*/

char	*search_multi(char *line)
{
	if (line_in_quote(line))
		return (NULL);
	/*{
		line = read_and_process_line(line);
		if (!line)
		{
			free(line);
			return (NULL);
		}
	}*/
	return (line);
}
