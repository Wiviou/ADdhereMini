/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:01:26 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/17 23:35:10 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_echo(t_struct **rr, char **t, t_sub **sub)
{
	if (ft_strncmp(t[(*rr)->ppp], "echo", 4) == 0 && t[(*rr)->ppp + 1] != NULL)
	{
		(*rr)->ppp++;
		while (ft_strncmp(t[(*rr)->ppp], ">", 1) != 0
			&& ft_strncmp(t[(*rr)->ppp], "<", 1) != 0
			&& ft_strncmp(t[(*rr)->ppp], ">>", 2) != 0
			&& ft_strncmp(t[(*rr)->ppp], "|", 1) != 0 && t[(*rr)->ppp])
		{
			if (ft_strncmp(t[(*rr)->ppp - 1], "echo", 4) == 0)
				(*rr)->c = COMMAND;
			else
				(*rr)->c = WORD;
			append_d(sub, t[(*rr)->ppp], (*rr)->c);
			(*rr)->ppp++;
		}
	}
	else
		(*rr)->ppp++;
}

static void	token_build(t_struct **rr, char **t, t_node **node, t_sub **sub)
{
	*sub = create_sub_node(t[(*rr)->ppp], (*rr)->c);
	append(node, *sub);
	(*rr)->verife = 1;
}

int	token_world(t_struct **rr, char **t, t_node **node, t_sub **sub)
{
	if ((*rr)->c == COMMAND && (*rr)->verife == 0 && (*rr)->redir == 0)
	{
		if (!token_command_0(rr, t, node, sub))
			return (0);
	}
	else if ((*rr)->c == PIPE)
		token_pipe(rr, t, node, sub);
	else if ((*rr)->c == REDIR_IN)
		token_in(rr, t, node, sub);
	else if ((*rr)->c == REDIR_OUT)
		token_out(rr, t, node, sub);
	else if ((*rr)->c == APPEND_REDIR_OUT)
		token_append(rr, t, node, sub);
	else if ((*rr)->c == BUILT_IN && (*rr)->verife == 0)
		token_build(rr, t, node, sub);
	else if ((*rr)->c == WORD || (*rr)->verife == 1 || (*rr)->redir == 1)
		token_word(rr, t, node, sub);
	(*rr)->iii++;
	token_echo(rr, t, sub);
	return (1);
}

int	token_pipx(t_struct **rr)
{
	int	v;

	v = 0;
	if ((*rr)->temp_str != NULL)
		free((*rr)->temp_str);
	(*rr)->vfv = (*rr)->r_pipe;
	(*rr)->state.piper = malloc(sizeof(int) *  ( 2 * (*rr)->nbr_pipe));
	if (!(*rr)->state.piper)
		return (0);
	while (v < (*rr)->nbr_pipe)
	{
		if (pipe((*rr)->state.piper + v * 2) < 0)
		{
			perror("ERR pipe ");
			exit(EXIT_FAILURE);
		}
		v++;
	}
	(*rr)->state.pide = malloc(sizeof(pid_t) * (2 + (*rr)->nbr_pipe));
	if (!(*rr)->state.pide)
		return (0);
	(*rr)->state.vg = (*rr)->state.gg;
	return (1);
}

void	token(char **t, t_node **node, t_sub **sub, t_struct **rr)
{
	static int	hh;

	init_token(rr);
	hh = 0;
	while (t[(*rr)->ppp] && t[(*rr)->ppp] != NULL)
	{
		(*rr)->c = tokennix(&t[(*rr)->ppp], rr, &hh);
		if ((*rr)->c == DEAD)
		{
			token_dead(rr, t, node, sub);
			return ;
		}
		if (!token_world(rr, t, node, sub))
			return ;
	}
	if (!token_pipx(rr))
		return ;
}
