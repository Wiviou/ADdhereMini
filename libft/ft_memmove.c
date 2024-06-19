/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                                '':''       */
/*   By: Jean Ruhlmann <@42.fr.Alsace>              |''/''|     ____:___      */
/*                                                      /    .'         .     */
/*   Created: 2023/08/11 21:40:59 by Jean Ruhlmann    |  ___/        0   |    */
/*   Updated: 2023/08/13 22:33:57 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == s)
		return (dest);
	if (s >= d || s + n <= d)
		while (n--)
			*d++ = *s++;
	else
	{
		d = d + n - 1;
		s = s + n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}
