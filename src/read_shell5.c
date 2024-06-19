/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:40:08 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:04:58 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	read_inn(t_struct **rr, t_node **node, char **command)
{
	(*rr)->state.s = 1;
	if ((*node)->next == NULL)
		printf("minishell: syntax error near unexpected token `newline'\n");
	delete_node(node);
	free_tab((void **)command);
	if ((*rr)->state.sss != NULL)
		free((*rr)->state.sss);
}

int	read_statek(int *jkl, t_struct **rr, t_node **node, char **command)
{
	if ((*rr)->state.kj > 1)
	{
		if (!read_fd00(command, rr))
			return (0);
		if (!read_fd1(command, rr, node))
			return (0);
		return (7);
	}
	else
	{
		read_jkll(jkl, rr, node, command);
		return (7);
	}
	return (1);
}

void	print_token_newline(void)
{
	printf("minishell: syntax error near unexpected token `newline'\n");
}

void	read_ambigus(t_struct **rr, t_node **node, char **command)
{
	if (((*rr)->state.is_redir && ft_strncmp(command[0], ">", 1) == 0)
		|| (ft_strncmp(command[0], ">>", 2) == 0 && (*rr)->state.is_append == 1)
		|| ft_strncmp(command[0], ">", 1) == 0)
	{
		if ((*node)->next == NULL)
		{
			if ((*rr)->ambigus == 1)
			{
				printf("Ambigus Redirect\n");
				(*rr)->interro = 1;
			}
			else
				print_token_newline();
		}
	}
}

void	read_state_pi(t_struct **rr, t_node **node, char **command)
{
	if (!(*rr)->state.is_redir && ft_strncmp(command[0], "|", 1) != 0)
	{
		(*rr)->state.k = 1;
		(*rr)->simple_file = 1;
	}
	free_tab((void **)command);
	delete_node(node);
	if ((*rr)->state.is_redir || (*rr)->state.is_append)
	{
		(*rr)->state.k = 1;
		(*rr)->state.kj++;
		(*rr)->state.is_redir = 0;
	}
	(*rr)->jkll = 1;
}
