/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 00:32:03 by jruhlman          #+#    #+#             */
/*   Updated: 2023/08/15 00:52:21 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*last_occurence;

	ch = (char)c;
	last_occurence = NULL;
	while (*s)
	{
		if (ch == *s)
			last_occurence = (char *)s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (last_occurence);
}
