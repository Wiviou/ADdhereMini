/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:00:57 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/13 09:05:44 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*find_by_pipe(t_node *head, int r_pipe)
{
	int	i;

	if (head == NULL || head->next == NULL)
		return (NULL);
	i = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->sub->dta->val, "|", 1) == 0)
		{
			i++;
			if (i == r_pipe)
				return (head);
		}
		head = head->next;
	}
	return (NULL);
}

void	insert_node(t_node **head, t_node *new_node, int r_pipe)
{
	t_node	*target_node;

	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	target_node = find_by_pipe(*head, r_pipe);
	if (target_node != NULL && target_node->next != NULL)
	{
		new_node->next = target_node->next;
		target_node->next = new_node;
	}
	else
		printf("error: fatal\n");
}

t_node	*find_by_val(t_node *head, t_struct **rr, int r_pipe)
{
	int	i;

	i = 0;
	while (head != NULL)
	{
		if (ft_strncmp(head->sub->dta->val, "|", 1) == 0)
			i++;
		if (head->sub && ft_strncmp(head->sub->dta->val, (*rr)->temp_str,
				ft_strlen((*rr)->temp_str)) == 0 && i == r_pipe)
			return (head);
		head = head->next;
	}
	return (NULL);
}

int	token_command0(t_node *new_node)
{
	new_node->sub = ft_calloc(1, sizeof(t_sub));
	if (!new_node->sub)
	{
		free(new_node);
		return (0);
	}
	new_node->sub->dta = ft_calloc(1, sizeof(t_dta));
	if (!new_node->sub->dta)
	{
		free(new_node->sub);
		free(new_node);
		return (0);
	}
	return (1);
}

int	token_command1(t_node *new_node, t_struct **rr, char **t)
{
	if (t[(*rr)->ppp])
	{
		new_node->sub->dta->val = strdup(t[(*rr)->ppp]);
		if (!new_node->sub->dta->val)
		{
			free(new_node->sub->dta);
			free(new_node->sub);
			free(new_node);
			return (0);
		}
	}
	else
		new_node->sub->dta->val = NULL;
	return (1);
}
