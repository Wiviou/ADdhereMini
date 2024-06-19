/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:06:28 by jruhlman          #+#    #+#             */
/*   Updated: 2024/04/02 13:08:28 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	cote_cote(char *in, t_struct **rr)
{
	while ((*rr)->i < (*rr)->len && ((*rr)->v == 1
			|| in[(*rr)->i] != ft_isspace(in[(*rr)->i])))
	{
		if ((in[(*rr)->i] == '\'' || in[(*rr)->i] == '\"') && (*rr)->v == 0)
		{
			(*rr)->quote = in[(*rr)->i++];
			(*rr)->v = 1;
		}
		if (in[(*rr)->i] != (*rr)->quote)
			(*rr)->out[(*rr)->j++] = in[(*rr)->i++];
		else
		{
			(*rr)->v = 0;
			(*rr)->i++;
		}
		if (ft_isspace(in[(*rr)->i]) && (*rr)->v == 0)
			break ;
	}
}

static char	*clean_quote(char *in, t_struct **rr)
{
	(*rr)->len = ft_strlen(in);
	(*rr)->out = malloc(sizeof(char) * ((*rr)->len + 1));
	if (!(*rr)->out)
		return (NULL);
	(*rr)->i = 0;
	(*rr)->j = 0;
	(*rr)->v = -1;
	while ((*rr)->i < (*rr)->len && (*rr)->v == -1)
	{
		if (in[(*rr)->i] == '\'' || in[(*rr)->i] == '\"')
		{
			(*rr)->v = 1;
			(*rr)->quote = in[(*rr)->i];
			(*rr)->i++;
			cote_cote(in, rr);
		}
		else
			(*rr)->out[(*rr)->j++] = in[(*rr)->i++];
	}
	(*rr)->out[(*rr)->j] = '\0';
	return ((*rr)->out);
}

char	**clean_quote_tab(char **tab, t_struct **rr)
{
	char	*temp;
	size_t	i;

	i = 0;
	while (tab[i])
	{
		temp = clean_quote(tab[i], rr);
		free(tab[i]);
		tab[i] = temp;
		i++;
	}
	return (tab);
}
