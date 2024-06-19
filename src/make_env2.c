/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:22:00 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/11 15:26:35 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	refact_env(t_envp **envp, t_struct **rr)
{
	int	v;

	(*rr)->f = 0;
	(*rr)->l = 0;
	(*rr)->g = 0;
	env_env(rr);
	(*rr)->key = ft_substr((*rr)->envv[(*rr)->i], 0, (*rr)->l);
	if (ft_strncmp((*rr)->key, "SHLVL", 5) == 0)
	{
		v = ft_atoi((*rr)->envv[(*rr)->i] + (*rr)->l + 1);
		v += 1;
		(*rr)->val = ft_itoa(v);
	}
	else
		(*rr)->val = ft_substr((*rr)->envv[(*rr)->i], (*rr)->l + 1, (*rr)->g);
	push_env(envp, (*rr)->key, (*rr)->val);
	(*rr)->i++;
}
