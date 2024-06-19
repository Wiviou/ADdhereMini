/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:56 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/13 09:04:04 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*replace_heredoc_with_tempfile(char *original_line, \
char **temp_filenames, int num_delimiters)
{
	char	*new_line;
	char	*curr;
	char	*out;
	int		i;
	char	*heredoc_start;

	new_line = allocate_new_line();
	if (!new_line)
		return (NULL);
	curr = original_line;
	out = new_line;
	i = 0;
	while (*curr && i < num_delimiters)
	{
		heredoc_start = strstr(curr, "<<");
		if (!heredoc_start)
			break ;
		curr += copy_until_heredoc(&out, curr, heredoc_start);
		curr += 2;
		curr = skip_heredoc_identifier(curr);
		insert_filename(&out, temp_filenames[i++]);
	}
	ft_strcpy(out, curr);
	return (new_line);
}

char	*allocate_new_line(void)
{
	return ((char *) malloc(1024));
}

int	copy_until_heredoc(char **dest, char *src, char *end)
{
	int	length;

	length = end - src;
	ft_strncpy(*dest, src, length);
	*dest += length;
	return (length);
}

char	*skip_heredoc_identifier(char *start)
{
	while (*start && ft_isspace(*start))
		start++;
	while (*start && !ft_isspace(*start))
		start++;
	return (start);
}

void	insert_filename(char **dest, char *filename)
{
	int	len;

	*(*dest)++ = ' ';
	len = strlen(filename);
	memcpy(*dest, filename, len);
	*dest += len;
	*(*dest)++ = ' ';
}
