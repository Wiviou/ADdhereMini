/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                                '':''       */
/*   By: Jean Ruhlmann <@42.fr.Alsace>              |''/''|     ____:___      */
/*                                                      /    .'         .     */
/*   Created: 2023/08/11 03:46:18 by Jean Ruhlmann    |  ___/        0   |    */
/*   Updated: 2023/10/21 21:55:06 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dest == src || !n)
		return (dest);
	d = (char *)dest;
	s = (const char *)src;
	while (n--)
	{
		*d++ = *s++;
	}
	return (dest);
}
