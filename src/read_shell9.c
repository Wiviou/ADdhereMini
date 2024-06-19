/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:54:18 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:32:13 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env_command(t_envp **envp)
{
	
	print_envp(*envp);
}

void	export_command(char **command, t_struct **rr, t_envp **envp)
{
	export_env(envp, command, rr);
}


