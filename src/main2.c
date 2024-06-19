/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:06:42 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:14:20 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	concat_n0e(char *line, t_n **catn)
{
	(*catn)->h = (*catn)->i + 3;
	(*catn)->start = (*catn)->h;
	(*catn)->h += 1;
	while (line[(*catn)->h])
	{
		while (ft_isspace(line[(*catn)->h]) && line[(*catn)->h])
			(*catn)->h++;
		if (line[(*catn)->h] && line[(*catn)->h] == '-' && line[(*catn)->h + 1]
			&& line[(*catn)->h + 1] == 'n')
		{
			(*catn)->sec = 1;
			(*catn)->h += 2;
			while (line[(*catn)->h] && line[(*catn)->h] == 'n')
				(*catn)->h += 1;
		}
		if ((line[(*catn)->h] && line[(*catn)->h] != '-'
				&& !ft_isspace(line[(*catn)->h])) || line[(*catn)->h] == '\0'
			|| (line[(*catn)->h] && line[(*catn)->h] == '-' && line[(*catn)->h
					+ 1] && line[(*catn)->h + 1] != 'n'))
			break ;
	}
	(*catn)->end = (*catn)->h;
	(*catn)->blend = (*catn)->h - (*catn)->start;
	(*catn)->i += 4;
}

void	concat_n0(char *line, t_n **catn)
{
	while (line[(*catn)->i])
	{
		if (line[(*catn)->i + 1] && line[(*catn)->i + 2] && line[(*catn)->i
				+ 3])
		{
			if (line[(*catn)->i] == 'e' && line[(*catn)->i + 1] == 'c'
				&& line[(*catn)->i + 2] == 'h' && line[(*catn)->i + 3] == 'o')
				concat_n0e(line, catn);
			else
				(*catn)->i++;
		}
		else
			(*catn)->i++;
	}
}

char	*concat_n(char *line, t_n **catn)
{
	char	*no_n;

	(*catn)->i = 0;
	(*catn)->h = 0;
	(*catn)->sec = 0;
	(*catn)->start = 0;
	(*catn)->end = 0;
	(*catn)->blend = 0;
	(*catn)->lend = 0;
	concat_n0(line, catn);
	(*catn)->lend = (*catn)->i - (*catn)->blend + 5;
	(*catn)->i = 0;
	no_n = malloc(sizeof(char) * ((*catn)->lend + 1));
	if (!no_n)
		return (NULL);
	if ((*catn)->sec)
	{
		concat_ni(catn, line, &no_n);
		return (no_n);
	}
	else
	{
		free(no_n);
		return (line);
	}
}

void	init_main(t_struct **rr, t_envp **envp, char **env)
{
	(*rr)->dead = 0;
	make_env(envp, env, rr);
	(*rr)->interro = 0;
	(*rr)->exit_nodig = 0;
	(*rr)->exit_to_many = 0;
	(*rr)->exit_val = 0;
	(*rr)->no_val = 0;
	(*rr)->plus = 0;
	(*rr)->ambigus = 0;
	(*rr)->is_cd = 0;
	stor_env(envp, rr);
}

int	check_struct(t_struct **rr, t_n **catn)
{
	*catn = malloc(sizeof(t_n));
	*rr = malloc(sizeof(t_struct));
	if (!*rr || !*catn)
		return (1);
	return (0);
}
