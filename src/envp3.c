/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:37 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/08 20:43:59 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_env_vars(t_struct **rr)
{
	int	n;

	n = 0;
	while ((*rr)->enve[n] != NULL)
		n++;
	return (n);
}

void	process_non_redir(int i, char **temp, t_struct **rr)
{
	while (i < count_env_vars(rr))
	{
		if (!(*rr)->state.is_redir)
		{
			see_export01(i, temp);
			i++;
		}
		else
		{
			break ;
		}
	}
}

void	process_redir(int i, char **temp, t_struct **rr)
{
	while (i < count_env_vars(rr))
	{
		if ((*rr)->state.is_redir)
		{
			see_export01(i, temp);
			i++;
		}
		else
		{
			break ;
		}
	}
}

void	export_env01(t_struct **rr, char **key_val, int i)
{
	while (key_val[i][(*rr)->f] != '=' && key_val[i][(*rr)->f] != '\0')
	{
		if (key_val[i][(*rr)->f] == '+' && key_val[i][(*rr)->f + 1] == '=')
			(*rr)->plus = 1;
		(*rr)->f++;
		(*rr)->l++;
	}
	if (key_val[i][(*rr)->f] != '\0')
		(*rr)->f++;
}

char	*export_env0(int i, char **key_val, t_struct **rr)
{
	int		y;
	char	*temp;

	(*rr)->f = 0;
	(*rr)->l = 0;
	(*rr)->g = 0;
	(*rr)->plus = 0;
	y = 0;
	while (key_val[i][y] != '=' && key_val[i][y] != '\0')
	{
		if (key_val[i][y] == '+' && key_val[i][y + 1] == '=')
			(*rr)->plus = 1;
		y++;
	}
	temp = ft_substr(key_val[i], 0, y - 1);
	export_env01(rr, key_val, i);
	while (key_val[i][(*rr)->f] && key_val[i][(*rr)->f] != '\0')
	{
		(*rr)->f++;
		(*rr)->g++;
	}
	return (temp);
}
