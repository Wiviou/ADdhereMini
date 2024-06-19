/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                              '':''         */
/*   By: jruhlman <jruhlman@student.42mulhouse.fr>|''/''|     ____:___        */
/*                                                    /    .'         .       */
/*   Created: 2024/06/09 13:16:42 by jruhlman       |  ___/        0   |      */
/*   Updated: 2024/06/09 13:17:17 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_get_endline(int fd, int out)
{
	char	*line;
	ssize_t	num_writt;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		num_writt = write(out, line, ft_strlen(line));
		if (num_writt == -1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
}

void	ft_lseek(int fd, const char *filename, mode_t mode)
{
	if (fd >= 0)
		close(fd);
	fd = open(filename, O_RDONLY, mode);
}
