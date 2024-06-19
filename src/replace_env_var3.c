/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:09:00 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/14 09:53:42 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_dollar_expansions(const char **str, char **temp, const char *end,
		t_struct **rr)
{
	if (*(*str + 1) == '?' || *(*str + 1) == '$')
		handle_special_variable(str, temp, end, rr);
	else
		handle_variable_replacement(str, temp, end, rr);
}

char	*perform_replacements(const char *str, size_t total_length,
		t_struct **rr)
{
	char	*temp;
	char	*end;

	(*rr)->rsult = malloc(total_length + 256);
	if (!(*rr)->rsult)
		return (NULL);
	temp = (*rr)->rsult;
	end = (*rr)->rsult + total_length;
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '"')
			handle_quotes(&str, &temp, end, rr);
		else if (*str == '$' && ft_isprint(*(str + 1)))
			handle_dollar_expansions(&str, &temp, end, rr);
		else
			*temp++ = *str++;
	}
	*temp = '\0';
	return ((*rr)->rsult);
}
