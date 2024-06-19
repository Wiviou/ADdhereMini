/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:51:31 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:48:09 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	read_co(t_struct **rr, t_envp **envp, char **command)
{
	(*rr)->state.is_build = 1;
	(*rr)->state.cmd_path = NULL;
	if ((ft_strncmp(command[0], "echo", 4) == 0 
		|| ft_strncmp(command[0], "export", 6) == 0
		|| ft_strncmp(command[0], "env", 3) == 0
		|| ft_strncmp(command[0], "pwd", 3) == 0)
		&& (*rr)->state.is_build != 7)
		(*rr)->state.is_build = 1;
			(*rr)->state.is_build = 0;
	if ((*rr)->state.is_out_in)
	{
		if ((*rr)->state.is_in)
		{
			command_exec2(command, envp, rr);
			(*rr)->state.x++;
		}
		else
		{
			command_exec1(command, envp, rr);
			(*rr)->state.x++;
		}
	}
	else
	{
		if ((*rr)->state.is_in)
		{
			command_exec3(command, envp, rr);
			(*rr)->state.x++;
		}
		else
			command_exec(command, envp, rr);
	}
}
