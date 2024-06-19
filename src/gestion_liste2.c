/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_liste2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:05:18 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/11 09:41:54 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_list_and(t_node **head_ref)
{
	t_node	*current;
	t_node	*temp;

	current = *head_ref;
	while (current != NULL)
	{
		delete_sub_list(&(current->sub));
		temp = current->next;
		free(current);
		current = temp;
	}
	*head_ref = NULL;
}
