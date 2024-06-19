/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_putnbr.c                                                    .         */
/*                                                                '':''       */
/*   By: Jean Ruhlmann <@42.fr.Alsace>              |''/''|     ____:___      */
/*                                                      /    .'         .     */
/*   Created: 2023/08/11 02:11:38 by Jean Ruhlmann    |  ___/        0   |    */
/*   Updated: 2023/08/11 02:13:50 by Jean Ruhlmann~^~^~^~^~^~^~^~^~^~^~^~^~   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb / 10)
	{
		ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	ft_putchar(nb % 10 + '0');
}
