/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:01:03 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/11 11:40:10 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	token_command2(t_struct **rr, char **t, t_node **node)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (0);
	if (!token_command0(new_node))
		return (0);
	if (!token_command1(new_node, rr, t))
		return (0);
	new_node->sub->dta->token = (*rr)->c;
	new_node->next = NULL;
	insert_node(node, new_node, (*rr)->r_pipe);
	return (1);
}

int	token_command(t_struct **rr, t_sub **sub, t_node **node, char **t)
{
	if ((*rr)->out_redir)
	{
		if (!(*rr)->vvvx)
		{
			*sub = create_sub_node(t[(*rr)->ppp], (*rr)->c);
			push(node, *sub);
		}
		else
		{
			if (!token_command2(rr, t, node))
				return (0);
		}
	}
	else
	{
		*sub = create_sub_node(t[(*rr)->ppp], (*rr)->c);
		append(node, *sub);
	}
	return (1);
}

void	token_dead(t_struct **rr, char **t, t_node **node, t_sub **sub)
{
	*sub = create_sub_node(t[(*rr)->ppp], (*rr)->c);
	append(node, *sub);
	if ((*rr)->temp_str != NULL)
		free((*rr)->temp_str);
}

int	token_command_0(t_struct **rr, char **t, t_node **node, t_sub **sub)
{
	if (!token_command(rr, sub, node, t))
		return (0);
	(*rr)->state.gg++;
	if ((*rr)->temp_str != NULL)
	{
		free((*rr)->temp_str);
		(*rr)->temp_str = NULL;
	}
	(*rr)->temp_str = ft_strdup(t[(*rr)->ppp]);
	(*rr)->verife = 1;
	return (1);
}

void	token_pipe(t_struct **rr, char **t, t_node **node, t_sub **sub)
{
	*sub = create_sub_node(t[(*rr)->ppp], (*rr)->c);
	append(node, *sub);
	
	(*rr)->verife = 0;
	(*rr)->out_redir = 0;
	(*rr)->vvvx = 1;
	(*rr)->r_pipe++;
	(*rr)->nbr_pipe++;
}
