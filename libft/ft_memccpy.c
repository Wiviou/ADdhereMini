/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                                '':''       */
/*   By: Jean Ruhlmann <@42.fr.Alsace>              |''/''|     ____:___      */
/*                                                      /    .'         .     */
/*   Created: 2023/08/11 05:21:29 by Jean Ruhlmann    |  ___/        0   |    */
/*   Updated: 2023/08/13 22:23:14 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
	{
		*d = *s;
		if (*s == (unsigned char)c)
		{
			return ((void *)(d + 1));
		}
		d++;
		s++;
	}
	return (NULL);
}
