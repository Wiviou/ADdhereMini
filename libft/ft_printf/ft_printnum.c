/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:53:45 by jruhlman          #+#    #+#             */
/*   Updated: 2023/11/14 17:53:51 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_digit(long num)
{
	int		count;
	char	digit;

	count = 0;
	if (num < 0)
	{
		write(1, "-", 1);
		count++;
		num = -num;
	}
	if (num >= 10)
		count += ft_digit(num / 10);
	digit = "0123456789"[num % 10];
	write(1, &digit, 1);
	return (count + 1);
}

int	ft_printnum(long num)
{
	return (ft_digit(num));
}
