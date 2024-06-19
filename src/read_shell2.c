/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:17:57 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:04:46 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	read_sous_filter(t_node **node, t_struct **rr)
{
	if ((ft_strncmp((*node)->next->next->next->sub->dta->val, "|", 1) == 0)
		&& (ft_strncmp((*node)->next->sub->dta->val, "<", 1) == 0))
		(*rr)->state.is_out_in = 1;
}

void	read_filter(t_node **node, t_struct **rr)
{
	if ((ft_strncmp((*node)->next->sub->dta->val, "|", 1) == 0))
		(*rr)->state.is_out_in = 1;
	else
		(*rr)->state.is_out_in = 0;
	if ((*node)->next->next)
		if ((*node)->next->next->next)
			read_sous_filter(node, rr);
	if (ft_strncmp((*node)->next->sub->dta->val, ">", 1) == 0
		&& ft_strncmp((*node)->sub->dta->val, "|", 1) != 0)
		(*rr)->state.is_redir = 1;
}

static void	read_sous_filter0(t_node **node, t_struct **rr)
{
	(*rr)->state.sss = NULL;
	t_node *n_temp = *node;

	while (n_temp != NULL && n_temp->next != NULL && n_temp->next->next != NULL && 
       n_temp->next->sub != NULL && n_temp->next->sub->dta != NULL && 
       n_temp->next->sub->dta->val != NULL &&
       ft_strncmp(n_temp->next->sub->dta->val, "<", 1) == 0)
	{
		if ((*rr)->state.sss != NULL)
			free((*rr)->state.sss);
		(*rr)->state.sss = NULL;
		(*rr)->state.sss = ft_strdup(n_temp->next->next->sub->dta->val);
		n_temp = n_temp->next->next;

	}
	if (n_temp->next != NULL)
	{
		if (ft_strncmp(n_temp->next->sub->dta->val, ">", 1) == 0)
			(*rr)->state.is_redir = 1;
	}
	if ((*node)->next->next->next)
	{
		if (ft_strncmp((*node)->next->next->next->sub->dta->val, ">", 1) == 0)
			(*rr)->state.is_redir = 1;
	}
}

void	read_filter0(t_node **node, t_struct **rr)
{
	if (ft_strncmp((*node)->next->sub->dta->val, ">>", 2) == 0)
		(*rr)->state.is_append = 1;
	if (ft_strncmp((*node)->next->sub->dta->val, "<", 1) == 0)
	{
		(*rr)->state.in_file = 1;
		if ((*node)->next->next != NULL)
			read_sous_filter0(node, rr);
	}
}

int	true_pwd(char **command, t_struct **rr, t_node **node)
{
	if ((*rr)->state.s)
	{
		free_tab((void **)command);
		(*rr)->state.s = 0;
		delete_node(node);
		return (0);
	}
	
	return (1);
}
