/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:07:08 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 09:05:16 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_special_variable(const char **ptr, char **temp, const char *end,
		t_struct **rr)
{
	char	*s;
	char	*pid_str;
	int		condition;

	condition = *(*ptr + 1);
	if (condition == '?')
	{
		//interro_state(rr);
		s = ft_itoa((*rr)->interro);
		if (s)
		{
			safe_append_string(temp, s, end);
			free(s);
		}
		*ptr += 2;
	}
	else if (condition == '$')
	{
		//sprintf(pid_str, "%d", getpid());
		pid_str = ft_itoa(getpid());
		safe_append_string(temp, pid_str, end);
		free(pid_str);
		*ptr += 2;
	}
}

size_t	handle_length_calculation(const char **ptr, t_struct **rr)
{
	const char	*start;
	const char	*end;
	char		*key;
	const char	*value;
	size_t		segment_length;

	start = (*ptr) + 1;
	end = start;
	while (ft_isprint(*end))
		end++;
	key = extract_env_key(start, end);
	value = get_env(key, rr);
	if (value)
		segment_length = ft_strlen(value);
	else
		segment_length = end - *ptr;
	free(key);
	*ptr = end;
	return (segment_length);
}

size_t	handle_dollar_signs(const char **str)
{
	size_t	length;

	length = 20;
	while (**str == '$')
		(*str)++;
	return (length);
}

size_t	handle_environment_variables(const char **str, t_struct **rr)
{
	const char	*start;
	char		*key;
	const char	*value;
	size_t		length;

	length = 0;
	start = *str;
	while (ft_isalnum(**str) || **str == '_')
		(*str)++;
	key = extract_env_key(start, *str);
	value = get_env(key, rr);
	if (value)
		length = ft_strlen(value);
	else
		length = (size_t)(*str - start);
	free(key);
	return (length);
}

size_t	handle_question_mark(const char **str, t_struct **rr)
{
	char	*temp;
	size_t	length;

	length = 0;
	temp = ft_itoa((*rr)->interro);
	length = ft_strlen(temp);
	free(temp);
	(*str)++;
	return (length);
}
