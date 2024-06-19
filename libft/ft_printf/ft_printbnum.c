/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:29:15 by jruhlman          #+#    #+#             */
/*   Updated: 2023/11/14 17:35:44 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_numba(unsigned int nbr, char *base)
{
	unsigned int		balen;
	unsigned int		nbrl;
	int					tot;

	tot = 0;
	nbrl = nbr;
	balen = 0;
	while (base[balen])
		balen++;
	if (nbrl >= balen)
	{
		tot += print_numba(nbrl / balen, base);
		tot += print_numba(nbrl % balen, base);
	}
	else
	{
		write(1, &base[nbrl], 1);
		tot++;
	}
	return (tot);
}

int	ft_printbnum(unsigned int nbr, int is_upper)
{
	if (is_upper)
		return (print_numba(nbr, "0123456789ABCDEF"));
	else
		return (print_numba(nbr, "0123456789abcdef"));
}
