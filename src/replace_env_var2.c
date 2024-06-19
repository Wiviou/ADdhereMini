/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:07:49 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/17 22:29:26 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	calculate_special_length(const char **str, t_struct **rr)
{
	size_t	length;

	length = 0;
	if (**str == '?')
	{
		length += handle_question_mark(str, rr);
	}
	else if (**str == '$')
	{
		length += handle_dollar_signs(str);
	}
	else
	{
		length += handle_environment_variables(str, rr);
	}
	return (length);
}

size_t	calculate_required_length(const char *str, t_struct **rr)
{
	size_t	length;

	length = 1;
	interro_state(rr);
	if (ft_strnstr(str, "$SHLVL", ft_strlen(str)) != NULL)
		length = ft_strlen(str);
	while (*str)
	{
		if (*str == '$' && ft_isprint(*(str + 1)))
		{
			str++;
			length += calculate_special_length(&str, rr);
		}
		else
		{
			length++;
			str++;
		}
	}
	return (length);
}

char	*extract_env_key(const char *start, const char *end)
{
	size_t	length;
	char	*key;

	length = end - start;
	key = malloc(length + 1);
	if (!key)
		return (NULL);
	memcpy(key, start, length);
	key[length] = '\0';
	return (key);
}

void	handle_variable_inside_quotes(const char **str, char **temp,
		const char *end, t_struct **rr)
{
	if (*(*str + 1) == '?' || *(*str + 1) == '$')
		handle_special_variable(str, temp, end, rr);
	else
		handle_variable_replacement(str, temp, end, rr);
}

void	handle_quotes(const char **str, char **temp, const char *end,
		t_struct **rr)
{
	int	quote_type;

	if (**str == '"')
		quote_type = 1;
	else
		quote_type = 0;
	*(*temp)++ = *(*str)++;
	while (**str && !(**str == '\'' && !quote_type) && !(**str == '"'
			&& quote_type))
	{
		if (**str == '$' && quote_type && ft_isprint(*(*str + 1)))
			handle_variable_inside_quotes(str, temp, end, rr);
		else
		{
			*(*temp)++ = *(*str)++;
		}
	}
	if (**str)
		*(*temp)++ = *(*str)++;
}
