/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:37 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/13 09:24:14 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	see_export(t_struct **rr)
{
	int		n;
	char	**temp;
	int		i;

	if ((*rr)->state.is_redir)
	{
		(*rr)->state.in_fd = open(".temp.txt", O_CREAT | O_TRUNC | O_RDWR,
				0644);
	}
	n = count_env_vars(rr);
	temp = see_export1(n, rr);
	i = 0;
	process_non_redir(i, temp, rr);
	process_redir(i, temp, rr);
	free(temp);
	if ( (*rr)->state.is_redir)
	{
		ft_get_line((*rr)->state.in_fd, 1);
		close((*rr)->state.in_fd);
	}
}

void	export_env1(t_envp **envp, t_struct **rr)
{
	if (!verife_env_and_del(envp, rr))
		append_envp(envp, (*rr)->key, (*rr)->val);
	else
	{
		free((*rr)->key);
		free((*rr)->val);
	}
}

void	export_env(t_envp **envp, char **key_val, t_struct **rr)
{
	int		i;
	char	*temp;

	i = 1;
	(*rr)->plus = 0;
	if (key_val[1] != NULL)
	{
		while (key_val[i] != NULL)
		{
			temp = export_env0(i, key_val, rr);
			if ((*rr)->plus)
				(*rr)->key = temp;
			else
				(*rr)->key = ft_substr(key_val[i], 0, (*rr)->l);
			(*rr)->val = ft_substr(key_val[i], (*rr)->l + 1, (*rr)->g);
			export_env1(envp, rr);
			if (!(*rr)->plus)
				free(temp);
			re_set_enve(envp, rr);
			i++;
		}
	}
	else
		see_export(rr);
}

int	andel(t_envp **envp, t_envp **prev, t_envp **cur, t_struct **rr)
{
	if (!(*rr)->plus)
	{
		ve_andel(envp, prev, cur);
		return (0);
	}
	else
	{
		ve_andel0(rr, cur);
		return (1);
	}
}
