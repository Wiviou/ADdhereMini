/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:21:31 by wkeiser           #+#    #+#             */
/*   Updated: 2024/06/13 09:05:13 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_within_double_quotes(const char *str, const char *pos)
{
	const char	*p;
	int			in_quotes;

	in_quotes = 0;
	p = str;
	while (p < pos)
	{
		if (*p == '"')
		{
			if (p == str || *(p - 1) != '\\')
			{
				in_quotes = 1 - in_quotes;
			}
		}
		p++;
	}
	return (in_quotes);
}

int	is_within_single_quotes(const char *str, const char *pos)
{
	const char	*p;
	int			in_quotes;

	in_quotes = 0;
	p = str;
	while (p < pos)
	{
		if (*p == '\'')
		{
			if (p == str || *(p - 1) != '\\')
			{
				in_quotes = 1 - in_quotes;
			}
		}
		p++;
	}
	return (in_quotes);
}

void	perform_variable_expansion(const char **str, char **temp,
		const char *end, t_struct **rr)
{
	int	in_single_quotes;
	int	in_double_quotes;

	while (*str && *temp < end)
	{
		if (**str == '$' && ft_isprint(*(*str + 1)))
		{
			(*rr)->state.is_build = 7;
			in_single_quotes = is_within_single_quotes(*str, *temp);
			if (!in_single_quotes)
			{
				in_double_quotes = is_within_double_quotes(*str, *temp);
				if (in_double_quotes)
				{
					handle_variable_replacement(str, temp, end, rr);
					continue ;
				}
			}
			**temp = *(*str)++;
		}
		else
			**temp = *(*str)++;
		(*temp)++;
	}
	**temp = '\0';
}

void	safe_append_string(char **dest, const char *src, const char *end)
{
	while (*src && *dest < end)
	{
		**dest = *src++;
		(*dest)++;
	}
}

void	handle_variable_replacement(const char **ptr, char **temp,
		const char *end, t_struct **rr)
{
	const char	*start;
	const char	*cursor;
	char		*key;
	const char	*value;
	int			is_value;

	start = (*ptr) + 1;
	cursor = start;
	while (ft_isalnum(*cursor) || *cursor == '_')
		cursor++;
	key = extract_env_key(start, cursor);
	value = get_env(key, rr);
	is_value = (value != NULL);
	if (is_value)
		safe_append_string(temp, value, end);
	else
		(*rr)->ambigus = 1;
	free(key);
	*ptr = cursor;
}
