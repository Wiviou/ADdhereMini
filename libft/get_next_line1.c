/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 05:31:19 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 10:44:41 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	find_nz(char *buffer)
{
	size_t	i;

	if (!buffer)
		return (-1);
	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buffer[i] == '\0' || buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}
