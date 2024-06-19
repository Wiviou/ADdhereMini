/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_reallox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:08:15 by jruhlman          #+#    #+#             */
/*   Updated: 2024/03/20 12:09:52 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*my_reallox(void *ptr, size_t new_size, size_t original_size)
{
	void	*new_ptr;
	size_t	minimal_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (original_size < new_size)
		minimal_size = original_size;
	else
		minimal_size = new_size;
	ft_memcpy(new_ptr, ptr, minimal_size);
	free(ptr);
	return (new_ptr);
}
