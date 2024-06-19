/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:01:12 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/11 11:40:44 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_token(t_struct **rr)
{
	(*rr)->ppp = 0;
	(*rr)->iii = 0;
	(*rr)->ff = 0;
	(*rr)->verife = 0;
	(*rr)->state.gg = 0;
	(*rr)->nbr_pipe = 0;
	(*rr)->state.vg = 0;
	(*rr)->redir = 0;
	(*rr)->out_redir = 0;
	(*rr)->vvvx = 0;
	(*rr)->r_pipe = 0;
	(*rr)->temp_str = NULL;
	(*rr)->porte = NULL;
	(*rr)->state.fff = 0;
	(*rr)->state.piper = NULL;
	(*rr)->state.pide = NULL;
	
}

void	token_in(t_struct **rr, char **t, t_node **node, t_sub **sub)
{
	*sub = create_sub_node(t[(*rr)->ppp], (*rr)->c);
	append(node, *sub);
	(*rr)->ff = 1;
	(*rr)->verife = 0;
	(*rr)->redir = 1;
	(*rr)->out_redir = 1;
}

void	token_out(t_struct **rr, char **t, t_node **node, t_sub **sub)
{
	*sub = create_sub_node(t[(*rr)->ppp], (*rr)->c);
	append(node, *sub);
	(*rr)->ff = 1;
	(*rr)->verife = 0;
	(*rr)->redir = 1;
	(*rr)->out_redir = 1;
}

void	token_append(t_struct **rr, char **t, t_node **node, t_sub **sub)
{
	*sub = create_sub_node(t[(*rr)->ppp], (*rr)->c);
	append(node, *sub);
	(*rr)->ff = 1;
	(*rr)->verife = 0;
	(*rr)->redir = 1;
	(*rr)->out_redir = 1;
}

void	token_word(t_struct **rr, char **t, t_node **node, t_sub **sub)
{
	t_node	*spe_node;

	if ((*rr)->iii == 0 || (*rr)->ff == 1)
	{
		*sub = create_sub_node(t[(*rr)->ppp], (*rr)->c);
		append(node, *sub);
		(*rr)->ff = 0;
	}
	else
	{
		if ((*rr)->redir)
			append_d(sub, t[(*rr)->ppp], (*rr)->c);
		else if ((*rr)->out_redir == 1)
		{
			spe_node = find_by_val(*node, rr, (*rr)->r_pipe);
			append_d(&(*spe_node).sub, t[(*rr)->ppp], (*rr)->c);
		}
		else
			append_d(sub, t[(*rr)->ppp], (*rr)->c);
	}
	if ((*rr)->redir == 1)
		(*rr)->redir = 0;
}
