/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:19:31 by jruhlman          #+#    #+#             */
/*   Updated: 2023/11/14 17:41:01 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	digitochar(unsigned int dig)
{
	if (dig < 10)
		return ('0' + dig);
	else
		return ('a' + (dig - 10));
}

static int	print_hex(unsigned long addr)
{
	int		count;
	char	chard;

	count = 0;
	if (addr >= 16)
		count += print_hex(addr / 16);
	chard = digitochar(addr % 16);
	write(1, &chard, 1);
	count++;
	return (count);
}

static int	print_prefix(void)
{
	write(1, "0x", 2);
	return (2);
}

int	ft_printptr(void *ptr)
{
	unsigned long	addr;
	int				count;

	count = 0;
	addr = (unsigned long)ptr;
	if (addr == 0)
		count += write(1, "0x0", 3);
	else
	{
		count += print_prefix();
		count += print_hex(addr);
	}
	return (count);
}
