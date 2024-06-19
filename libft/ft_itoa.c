/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:56:56 by jruhlman          #+#    #+#             */
/*   Updated: 2023/10/21 22:24:29 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_digit(int n)
{
	size_t	i;

	i = 1;
	while (n != '\0')
	{
		n /= 10;
		if (n != 0)
			i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	size_t		digit;
	long int	num;
	char		*strn;

	num = n;
	digit = ft_digit(n);
	if (n < 0)
	{
		num *= -1;
		digit++;
	}
	strn = (char *)malloc(sizeof(char) * (digit + 1));
	if (!strn)
		return (NULL);
	strn[digit] = '\0';
	while (digit--)
	{
		strn[digit] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		strn[0] = '-';
	return (strn);
}
