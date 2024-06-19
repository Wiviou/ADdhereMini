/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:28:43 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:06:49 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	int	fd;

	if (sig == SIGINT && !g_child_running)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		printf("\n");
	}
	fd = open(".interro.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
	ft_putnbr_fd(130, fd);
	close(fd);
}

void	handle_sigquit(int sig)
{
	int	fd;

	if (sig == SIGQUIT)
	{
		rl_reset_terminal(NULL);
		write(STDOUT_FILENO, "Quit\n", 5);
		g_child_running = 0;
		setup_sigint_handler();
		fd = open(".interro.txt", O_TRUNC | O_CREAT | O_RDWR, 0644);
		ft_putnbr_fd(131, fd);
		close(fd);
	}
}

void	setup_sigint_handler(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	if (g_child_running)
		sa_quit.sa_handler = handle_sigquit;
	else
		sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	ft_echo_co(char **echo_tab, t_struct **rr)
{
	int	i;
	int	f;

	(*rr)->interro = 0;
	(*rr)->ffd = open(".tmmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!(*rr)->ffd)
		return ;
	i = 1;
	f = 0;
	if (echo_tab[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(echo_tab[i], "-n", 2) == 0 && echo_tab[i][2] == '\0')
	{
		f = 1;
		i++;
	}
	echo_tab_fd(i, echo_tab, rr, f);
}
