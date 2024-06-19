/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:48:18 by jruhlman          #+#    #+#             */
/*   Updated: 2023/11/14 17:52:48 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_undig(unsigned long num)
{
	int		count;
	char	digit;

	count = 0;
	if (num >= 10)
		count += print_undig(num / 10);
	digit = "0123456789"[num % 10];
	write(1, &digit, 1);
	return (count + 1);
}

int	ft_printunum(unsigned long num)
{
	return (print_undig(num));
}
