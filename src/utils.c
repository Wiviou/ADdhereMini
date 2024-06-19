/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:06:47 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:42:36 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	wait_pid2(int *status, t_stat *state)
{
	int	fd;

	unlink(".interro.txt");
	int	exit_v = WEXITSTATUS(*status);
	fd = open(".interro.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (state->is_build == 1)
		ft_putnbr_fd(0, fd);
	else if (exit_v == 2)
		ft_putnbr_fd(1, fd);
	close(fd);
}

void	wait_pid(t_stat **state)
{
	int	i;
	int	status;

	i = 0;
	if (!(*state)->vg)
	{
		while (i < (*state)->gg)
		{
			waitpid((*state)->pide[i], &status, 0);
			i++;
			if (WIFEXITED(status))
				wait_pid2(&status, *state);
		}
		g_child_running = 0;
		setup_sigint_handler();
	}
}

int	ft_str_isdigit(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_tab(void **f)
{
	int	i;

	i = 0;
	if (*f == NULL || f == NULL)
	{
		free(f);
		return ;
	}
	while (f[i])
	{
		free(f[i]);
		i++;
	}
	free(f);
}

void	ft_get_line(int fd, int out)
{
	char	*lune;

	while (1)
	{
		lune = get_next_line(fd);
		if (!lune)
			break ;
		write(out, lune, ft_strlen(lune));
		free(lune);
	}
	close(fd);
}
