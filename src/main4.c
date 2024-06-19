/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:43:16 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:14:15 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	concat_ni(t_n **catn, char *line, char **no_n)
{
	while (line[(*catn)->i] && (*catn)->i < (*catn)->start + 1)
	{
		(*no_n)[(*catn)->i] = line[(*catn)->i];
		(*catn)->i++;
	}
	(*no_n)[(*catn)->i++] = ' ';
	(*no_n)[(*catn)->i++] = '-';
	(*no_n)[(*catn)->i++] = 'n';
	(*no_n)[(*catn)->i++] = ' ';
	while (line[(*catn)->end])
	{
		(*no_n)[(*catn)->i++] = line[(*catn)->end++];
	}
	(*no_n)[(*catn)->i] = '\0';
	free(line);
}

void	init_main_read(t_t **k_)
{
	(*k_)->rr->dead = 0;
	(*k_)->rr->state.piper = NULL;
	(*k_)->rr->state.pide = NULL;
}

int	pro_main(t_t **k_, char **processed_line)
{
	*processed_line = search_multi(*processed_line);
	if (!*processed_line)
	{
		printf("Syntaxe Error\n");
		if ((*k_)->rr->rsult != NULL)
			free((*k_)->rr->rsult);
		free(*processed_line);
		destroy_file();
		delete_list_and(&(*k_)->node);
		return (7);
	}
	*processed_line = clean_concat(*processed_line);
	return (1);
}
