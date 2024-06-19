/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:44:21 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/11 16:13:35 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	read_exitn(t_struct **rr, char **command)
{
	if (command[2] != NULL)
	{
		free_tab((void **)command);
		(*rr)->exit_to_many = 1;
		(*rr)->exit_nodig = 0;
		return (1);
	}
	else
	{
		(*rr)->exit_to_many = 0;
		(*rr)->exit_nodig = 0;
		(*rr)->exit_val = ft_atoi(command[1]);
		free_tab((void **)command);
		return (1);
	}
	return (0);
}

static int	read_exitw(t_struct **rr, char **command)
{
	if (!ft_str_isdigit(command[1]))
	{
		(*rr)->exit_nodig = 1;
		(*rr)->exit_to_many = 0;
		free_tab((void **)command);
		return (1);
	}
	else if (ft_str_isdigit(command[1]))
	{
		if (read_exitn(rr, command))
			return (1);
	}
	return (0);
}

int	read_exitx(t_struct **rr, char **command, t_node **node)
{
	t_stat	state;
	t_stat	*state_ptr;

	if ((*rr)->jkll)
	{
		state = (*rr)->state;
		free_tab((void **)command);
		delete_node(node);
		state_ptr = &state;
		wait_pid(&state_ptr);
		return (7);
	}
	if (command[1] != NULL)
	{
		if (read_exitw(rr, command))
			return (1);
	}
	else
	{
		free_tab((void **)command);
		return (1);
	}
	return (0);
}

void	read_now(t_struct **rr, char **command, t_envp **envp)
{
	if ((*rr)->state.is_out_in)
	{
		if ((*rr)->state.is_in)
		{
			command_exec_now2(command, envp, rr);
			(*rr)->state.x++;
		}
		else
		{
			command_exec_now1(command, envp, rr);
			(*rr)->state.x++;
		}
	}
	else
	{
		if ((*rr)->state.is_in)
		{
			command_exec_now3(command, envp, rr);
			(*rr)->state.x++;
		}
		else
			command_exec_now(command, envp, rr);
	}
}
