/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkeiser <wkeiser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:22:44 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/11 09:36:30 by wkeiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../libft/libft.h"

char	**free_mem(char **tab, size_t id)
{
	while (id)
		free(tab[--id]);
	free(tab);
	return (NULL);
}

void	is_in_quote(char c, int *in, int *inn)
{
	if (c == '\'')
	{
		*in = !*in;
	}
	if (c == '\"')
	{
		*inn = !*inn;
	}
}
