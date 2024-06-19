/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                                '':''       */
/*   By: Jean Ruhlmann <@42.fr.Alsace>              |''/''|     ____:___      */
/*                                                      /    .'         .     */
/*   Created: 2023/08/12 02:27:32 by Jean Ruhlmann    |  ___/        0   |    */
/*   Updated: 2023/08/13 22:26:05 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		ch;

	ptr = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*ptr == ch)
		{
			return ((void *)ptr);
		}
		ptr++;
	}
	return (NULL);
}
