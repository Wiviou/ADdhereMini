/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_d_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:16:27 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/09 13:04:10 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_sub	*create_sub_node(char *val, t_token c)
{
	t_sub	*new_sub;

	if (!val)
		return (NULL);
	new_sub = malloc(sizeof(t_sub));
	if (!new_sub)
		return (NULL);
	new_sub->dta = malloc(sizeof(t_dta));
	if (!new_sub->dta)
	{
		free(new_sub);
		return (NULL);
	}
	new_sub->dta->val = ft_strdup(val);
	if (!new_sub->dta->val)
	{
		free(new_sub->dta);
		free(new_sub);
		return (NULL);
	}
	new_sub->dta->token = c;
	new_sub->next = NULL;
	return (new_sub);
}

void	push_d(t_sub **head_ref, char *val, t_token c)
{
	t_sub	*new_sub;

	new_sub = create_sub_node(val, c);
	new_sub->next = *head_ref;
	*head_ref = new_sub;
}

void	append_d(t_sub **head_ref, char *val, t_token c)
{
	t_sub	*new_node;
	t_sub	*last;

	new_node = create_sub_node(val, c);
	if (!head_ref)
		return ;
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

void	print_sub(t_sub *sub)
{
	while (sub != NULL)
	{
		printf("%s ", sub->dta->val);
		printf("%d ", sub->dta->token);
		sub = sub->next;
	}
	printf("\n");
}

void	delete_sub_list(t_sub **head_ref)
{
	t_sub	*current;
	t_sub	*temp;

	current = *head_ref;
	while (current != NULL)
	{
		temp = current->next;
		free(current->dta->val);
		free(current->dta);
		free(current);
		current = temp;
	}
	*head_ref = NULL;
}
