/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:30:13 by jruhlman          #+#    #+#             */
/*   Updated: 2023/08/18 22:37:14 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoined;
	size_t	len_1;
	size_t	len_2;

	if (!s1 || !s2)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	strjoined = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!strjoined)
		return (NULL);
	ft_strcpy(strjoined, s1);
	ft_strcat(strjoined, s2);
	return (strjoined);
}
