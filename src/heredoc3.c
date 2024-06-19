/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:40:56 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/13 09:04:01 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_final_tempfile(char *final_tempfile)
{
	int		final_fd;
	char	*pid_str;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (-1);
	ft_strcpy(final_tempfile, "/tmp/final_heredoc_");
	ft_strcat(final_tempfile, pid_str);
	free(pid_str);
	final_fd = open(final_tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (final_fd == -1)
		perror("Error opening final tempfile");
	return (final_fd);
}

void	copy_single_tempfile(int final_fd, char *temp_filename)
{
	char	buffer[1024];
	int		temp_fd;
	ssize_t	bytes_read;

	temp_fd = open(temp_filename, O_RDONLY);
	if (temp_fd == -1)
	{
		perror("Error opening tempfile for reading");
		return ;
	}
	bytes_read = read(temp_fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(final_fd, buffer, bytes_read);
		bytes_read = read(temp_fd, buffer, sizeof(buffer));
	}
	close(temp_fd);
}

void	copy_tempfiles_to_final(char **temp_filenames, int num_delimiters,
		int final_fd)
{
	int	i;

	i = 0;
	while (i < num_delimiters)
	{
		if (temp_filenames[i])
		{
			copy_single_tempfile(final_fd, temp_filenames[i]);
		}
		i++;
	}
}

void	exe_command(char *cmd, char *final_tempfile, char **temp_filenames,
		int num_delimiters)
{
	char	final_cmd[4096];
	char	*argv[4];
	int		status;
	int		i;

	ft_strcpy(final_cmd, cmd);
	ft_strcat(final_cmd, " < ");
	ft_strcat(final_cmd, final_tempfile);
	argv[0] = "/bin/sh";
	argv[1] = "-c";
	argv[2] = final_cmd;
	argv[3] = NULL;
	status = execute_here_command(argv);
	if (status == 0)
	{
		i = 0;
		while (i < num_delimiters)
		{
			if (temp_filenames[i])
				unlink(temp_filenames[i]);
			i++;
		}
		unlink(final_tempfile);
	}
}

void	cleanup_heredoc(t_heredoc_data_t *h)
{
	if (!h)
		return ;
	cleanup_delimiters_and_tempfiles(h->delimiters, h->temp_filenames,
		h->num_delimiters);
}
