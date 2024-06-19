/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                                '':''       */
/*   By: Jean Ruhlmann <@42.fr.Alsace>              |''/''|     ____:___      */
/*                                                      /    .'         .     */
/*   Created: 2023/08/13 03:51:43 by Jean Ruhlmann    |  ___/        0   |    */
/*   Updated: 2023/08/14 00:29:25 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*original_dest;

	original_dest = dest;
	while (*dest)
		dest++;
	while (n && *src)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	return (original_dest);
}
