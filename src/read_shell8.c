/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell8.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:54:18 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 23:23:57 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	read_part1(int *jkl, char **command, t_struct **rr, t_node **node)
{
	int	hek;

	if (!true_pwd(command, rr, node))
		return (7);
	if ((*rr)->state.k)
	{
		hek = read_statek(jkl, rr, node, command);
		if (hek == 7)
			return (7);
		else if (hek == 0)
			return (0);
	}
	return (1);
}

int	read_part2(t_envp **envp, char **command, t_struct **rr, t_node **node)
{
	int	v;

	v = 0;
	if (ft_strncmp(command[0], "cd", 2) == 0)
	{
		if (read_cd(command, rr, node, envp) == 7)
		{
			free((*rr)->lun);
			return (7);
		}
		v = 1;
	}
	else if (ft_strncmp(command[0], "<", 1) == 0)
	{
		read_inn(rr, node, command);
		return (7);
	}
	if (v)
	{
		delete_node(node);
		free_tab((void **)command);
		free((*rr)->lun);
		return (7);
	}
	return (1);
}

int	read_part3(char **command, t_node **node, t_struct **rr)
{
	int	hek;

	if (ft_strncmp(command[0], "|", 1) == 0 || ft_strncmp(command[0], ">",
			1) == 0)
	{
		read_ambigus(rr, node, command);
		read_state_pi(rr, node, command);
		return (7);
	}
	else if (ft_strncmp(command[0], "exit", 4) == 0)
	{
		hek = read_exitx(rr, command, node);
		if (hek == 7)
			return (7);
		else if (hek == 1)
			return (1);
	}
	return (0);
}

int	read_concat(char **command, t_node **node, t_struct **rr)
{
	int	hek;

	hek = read_part3(command, node, rr);
	if (hek == 7)
		return (7);
	else if (hek == 1)
		return (1);
	return (0);
}

void	compacte_read(t_struct **rr, t_envp **envp, char **command, t_node **node)
{
	if (ft_strncmp(command[0], "./", 2) == 0)
		read_now(rr, command, envp);
	else  if (command_exist(command[0], rr))
	{
		(*rr)->state.cmd_path = NULL;
		read_co(rr, envp, command);
	}
	free_tab((void **)command);
	if ((*rr)->lun != NULL)
		free((*rr)->lun);
	(*rr)->lun = NULL;
	delete_node(node);
}
