/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_liste.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:05:18 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/11 09:41:05 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*create_node(t_sub *sub)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->sub = sub;
	new_node->next = NULL;
	return (new_node);
}

void	push(t_node **head_ref, t_sub *sub)
{
	t_node	*new_node;

	new_node = create_node(sub);
	new_node->next = *head_ref;
	*head_ref = new_node;
}

void	append(t_node **head_ref, t_sub *sub)
{
	t_node	*new_node;
	t_node	*last;

	new_node = create_node(sub);
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return ;
	}
	last = *head_ref;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

void	print_list(t_node *node)
{
	while (node != NULL)
	{
		print_sub(node->sub);
		node = node->next;
	}
	printf("\n");
}

void	delete_node(t_node **node_ref)
{
	t_node	*to_del;

	if (node_ref == NULL || *node_ref == NULL)
		return ;
	delete_sub_list(&((*node_ref)->sub));
	to_del = *node_ref;
	*node_ref = (*node_ref)->next;
	free(to_del);
}
