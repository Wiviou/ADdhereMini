/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shell1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 01:13:29 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/11 15:56:41 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	node_command0(t_sub **sub, char ***temp, char **tab)
{
	**temp = ft_strdup((*sub)->dta->val);
	if (!**temp)
	{
		while (*temp > tab)
			free(*(--(*temp)));
		free(tab);
		return (0);
	}
	(*temp)++;
	*sub = (*sub)->next;
	return (1);
}

char	**node_command(t_sub **sub)
{
	char	**tab;
	char	**temp;
	int		count;
	t_sub	*current;

	count = 0;
	current = *sub;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	temp = tab;
	while (*sub != NULL)
	{
		if (!node_command0(sub, &temp, tab))
			return (NULL);
	}
	*temp = NULL;
	return (tab);
}

void	interro_state(t_struct **rr)
{
	char	*s;
	int		fd;

	fd = open(".interro.txt", O_RDONLY, 0644);
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		(*rr)->interro = ft_atoi(s);
		free(s);
	}
	unlink(".interro.txt");
	close(fd);
}

static void	st_cat(t_node **node, t_struct **rr)
{
	t_node	*temp;

	temp = *node;
	while (temp && temp->next)
	{
		if (temp->sub->next == NULL)
			(*rr)->is_cat += 1;
		temp = temp->next->next;
	}
}

void	init_stcat(t_node **node, t_struct **rr)
{
	(*rr)->state.is_kate = 0;
	(*rr)->state.is_out_in = 0;
	(*rr)->state.is_in = 0;
	(*rr)->state.x = 0;
	(*rr)->state.y = -1;
	(*rr)->state.is_redir = 0;
	(*rr)->state.k = 0;
	(*rr)->state.kj = 0;
	(*rr)->state.kkk = NULL;
	(*rr)->state.s = 0;
	(*rr)->state.in_file = 0;
	(*rr)->state.sss = NULL;
	(*rr)->state.is_in_echo = 0;
	(*rr)->simple_file = 0;
	(*rr)->state.is_append = 0;
	(*rr)->is_cat = 0;
	(*rr)->jkll = 0;
	(*rr)->is_cat = 0;
	st_cat(node, rr);
	(*rr)->built_in = 0;
	(*rr)->is_cd = 0;
}
