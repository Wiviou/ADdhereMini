/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:42:14 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/10 15:20:54 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	insertion_sort(char **temp, int n)
{
	int		i;
	char	*key;
	int		j;
	int		compare_result;

	i = 1;
	while (i < n)
	{
		key = temp[i];
		j = i - 1;
		while (j >= 0)
		{
			compare_result = ft_memcmp(temp[j], key, ft_strlen(temp[i]));
			if (compare_result <= 0)
				break ;
			temp[j + 1] = temp[j];
			j--;
		}
		temp[j + 1] = key;
		i++;
	}
}

char	**allocate_and_copy(int n, t_struct **rr)
{
	char	**temp;
	int		i;

	temp = malloc(sizeof(char *) * n);
	if (!temp)
		return (NULL);
	i = 0;
	while (i < n)
	{
		temp[i] = (*rr)->enve[i];
		i++;
	}
	return (temp);
}

char	**see_export1(int n, t_struct **rr)
{
	char	**temp;

	temp = allocate_and_copy(n, rr);
	if (!temp)
		return (NULL);
	insertion_sort(temp, n);
	return (temp);
}

void	see_export01(int i, char **temp)
{
	int	f;

	f = 0;
	write(1, "declare -x ", 11);
	while (temp[i][f] != '=' && temp[i][f] != '\0')
	{
		write(1, &temp[i][f], 1);
		f++;
	}
	if (temp[i][f] == '=' && temp[i][f + 1] != '\0')
	{
		write(1, "=\"", 2);
		f++;
		while (temp[i][f] != '\0')
		{
			write(1, &temp[i][f], 1);
			f++;
		}
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	see_export02(int i, char **temp, t_struct **rr)
{
	int	f;

	f = 0;
	ft_putstr_fd("declare -x ", (*rr)->state.in_fd);
	while (temp[i][f] != '=' && temp[i][f] != '\0')
		ft_putchar_fd(temp[i][f++], (*rr)->state.in_fd);
	if (temp[i][f] == '=' && temp[i][f + 1] != '\0')
	{
		ft_putstr_fd("=\"", (*rr)->state.in_fd);
		f++;
		while (temp[i][f] != '\0')
			ft_putchar_fd(temp[i][f++], (*rr)->state.in_fd);
		ft_putchar_fd('\"', (*rr)->state.in_fd);
	}
	ft_putchar_fd('\n', (*rr)->state.in_fd);
	
}
