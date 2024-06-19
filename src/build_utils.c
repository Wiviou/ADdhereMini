/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:39:27 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:31:35 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	echo_see(t_struct **rr)
{
	ft_lseek((*rr)->ffd, ".tmmp.txt", 0644);
	ft_get_line((*rr)->ffd, 1);
	unlink(".tmmp.txt");
}

void	echo_tab_fd(int i, char **echo_tab, t_struct **rr, int f)
{
	while (echo_tab[i])
	{
		if (i > 1 && f == 0)
			ft_putchar_fd(' ', (*rr)->ffd);
		else if (i > 2 && f == 1)
			ft_putchar_fd(' ', (*rr)->ffd);
		ft_putstr_fd(echo_tab[i], (*rr)->ffd);
		i++;
	}
	if (f == 0)
		ft_putchar_fd('\n', (*rr)->ffd);

	echo_see(rr);
	close((*rr)->ffd);
}
