/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 23:33:23 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 15:47:39 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	filter_read(t_struct **rr, t_node **node)
{
	if ((*node)->next != NULL)
	{
		read_filter(node, rr);
		read_filter0(node, rr);
	}
	else
		(*rr)->state.is_out_in = 0;
}

int	read_hek(char **command, t_node **node, t_struct **rr, t_envp **envp)
{
	int	jkl;
	int	hek;

	hek = read_part1(&jkl, command, rr, node);
	if (hek == 7)
		return (7);
	else if (hek == 0)
		return (0);
	hek = read_part2(envp, command, rr, node);
	if (hek == 7)
		return (7);
	hek = read_concat(command, node, rr);
	if (hek == 7)
		return (7);
	else if (hek == 1)
		return (1);
	return (2);
}

void	if_clear(t_struct **rr)
{
	if ((*rr)->state.is_redir == 1)
	{
		if ((*rr)->state.kkk != NULL)
		{
			free((*rr)->state.kkk);
			(*rr)->state.kkk = NULL;
		}
	}
}

int	read_shell(t_node **node, t_envp **envp, t_struct **rr, char **env)
{
	int		hek;
	char	**command;
	t_sub	*sub;

	init_stcat(node, rr);
	while (*node != NULL)
	{
		filter_read(rr, node);
		sub = (*node)->sub;
		command = node_command(&sub);
		hek = read_hek(command, node, rr, envp);
		if (hek == 1)
			return (1);
		else if (hek == 0)
			return (0);
		
		else if (hek == 7)
			continue ;
		(*rr)->eeenv = env;
		compacte_read(rr, envp, command, node);
	}
	if_clear(rr);
	return (0);
}
