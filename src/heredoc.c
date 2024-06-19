/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:56 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/11 09:42:58 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_and_write_tempfile(char *filename, char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_line_to_fd(fd, line);
		free(line);
	}
	close(fd);
	return (0);
}

char	**allocate_temp_filenames(int num_delimiters)
{
	char	**temp_filenames;
	int		i;

	temp_filenames = malloc(sizeof(char *) * (num_delimiters + 1));
	if (!temp_filenames)
		return (NULL);
	i = 0;
	while (i < num_delimiters)
	{
		temp_filenames[i] = generate_unique_temp_filename();
		if (!temp_filenames[i])
		{
			while (i > 0)
			{
				i--;
				free(temp_filenames[i]);
			}
			free(temp_filenames);
			return (NULL);
		}
		i++;
	}
	temp_filenames[num_delimiters] = NULL;
	return (temp_filenames);
}

char	**handle_heredocs(char **delimiters, int num_delimiters)
{
	char	**temp_filenames;
	int		i;

	temp_filenames = allocate_temp_filenames(num_delimiters);
	if (!temp_filenames)
		return (NULL);
	i = 0;
	while (i < num_delimiters)
	{
		if (open_and_write_tempfile(temp_filenames[i], delimiters[i]) == -1)
		{
			free(temp_filenames[i]);
			temp_filenames[i] = NULL;
		}
		i++;
	}
	return (temp_filenames);
}

char	*generate_unique_temp_filename(void)
{
	static int	counter = 0;
	char		*filename;
	char		*counter_str;

	filename = malloc(sizeof(char) * 256);
	if (!filename)
	{
		perror("Failed to allocate memory for filename");
		return (NULL);
	}
	ft_strcpy(filename, "/tmp/heredoc_");
	counter_str = ft_itoa(counter);
	if (!counter_str)
	{
		free(filename);
		return (NULL);
	}
	ft_strcat(filename, counter_str);
	free(counter_str);
	counter++;
	return (filename);
}

int	count_heredoc_delimiters(char *line)
{
	int		count;
	char	*start;
	char	*next_start;

	count = 0;
	start = line;
	next_start = ft_strnstr(start, "<<", strlen(start));
	while (next_start)
	{
		count++;
		start = next_start + 2;
		next_start = ft_strnstr(start, "<<", strlen(start));
	}
	return (count);
}
