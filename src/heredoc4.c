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

char	*process_heredocs(char *line)
{
	t_heredoc_data_t	h;
	char				*modified_line;

	h.delimiters = extract_delimiters(line, &h.num_delimiters);
	if (!h.delimiters || h.num_delimiters == 0)
		return (line);
	h.temp_filenames = handle_heredocs(h.delimiters, h.num_delimiters);
	if (!h.temp_filenames)
	{
		cleanup_delimiters_and_tempfiles(h.delimiters, NULL, h.num_delimiters);
		return (line);
	}
	modified_line = replace_heredoc_with_tempfile(line, h.temp_filenames, \
													h.num_delimiters);
	if (modified_line)
	{
		free(line);
		line = modified_line;
	}
	cleanup_delimiters_and_tempfiles(h.delimiters, h.temp_filenames, \
										h.num_delimiters);
	return (line);
}

void	write_line_to_fd(int fd, const char *line)
{
	char	*formatted_line;

	formatted_line = malloc(ft_strlen(line) + 2);
	if (!formatted_line)
	{
		perror("Fatal error: failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	if (formatted_line)
	{
		ft_strcpy(formatted_line, line);
		ft_strcat(formatted_line, "\n");
		write(fd, formatted_line, ft_strlen(formatted_line));
		free(formatted_line);
	}
}

char	*split_command(char *line)
{
	char	*cmd_end;

	cmd_end = ft_strnstr(line, "<<", strlen(line));
	if (cmd_end)
	{
		*cmd_end = '\0';
		return (line);
	}
	return (NULL);
}

int	execute_here_command(char **argv)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	pid = fork();
	if (pid == -1)
	{
		perror("Failed to fork process");
		return (-1);
	}
	if (pid == 0)
		execute_child_process(argv);
	else if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == 0)
				return (0);
			else
				return (exit_status);
		}
	}
	return (-1);
}

void	execute_child_process(char **argv)
{
	execve("/bin/sh", argv, NULL);
	perror("execve failed");
	exit(EXIT_FAILURE);
}
