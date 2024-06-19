/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                                '':''       */
/*   By: Jean Ruhlmann <@42.fr.Alsace>              |''/''|     ____:___      */
/*                                                      /    .'         .     */
/*   Created: 2023/08/13 03:39:36 by Jean Ruhlmann    |  ___/        0   |    */
/*   Updated: 2023/08/14 00:26:21 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*original_dest;

	original_dest = dest;
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}
