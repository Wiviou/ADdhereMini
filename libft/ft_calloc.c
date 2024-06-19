/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:25:33 by jruhlman          #+#    #+#             */
/*   Updated: 2023/10/19 12:34:40 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*alloc;
	size_t	i;
	size_t	total_size;

	total_size = nmemb * size;
	if (nmemb && size && total_size / nmemb != size)
		return (NULL);
	alloc = (char *)malloc(total_size);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		alloc[i++] = 0;
	}
	return (alloc);
}
