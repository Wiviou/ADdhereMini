/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jruhlman <jruhlman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 05:31:19 by jruhlman          #+#    #+#             */
/*   Updated: 2024/06/13 10:45:51 by jruhlman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strlgjoin(char *s1, char *s2, int *r_l)
{
	char	*dest;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dest = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	ft_memcpy(dest, s1, len1);
	free(s1);
	ft_memcpy(dest + len1, s2, len2 + 1);
	if (len1 + len2 > 0 && *(dest + len1 + len2 - 1) == '\n')
		*r_l = 0;
	return (dest);
}

static void	ft_strlgcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while (src[i] && i < n - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
}

static char	*extracte_line(char *line, char *statix, int *r_l, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	readed;
	size_t	npoint;

	while (*r_l == -1)
	{
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free(line);
			ft_bzero(statix, (BUFFER_SIZE + 1));
			return (NULL);
		}
		npoint = find_nz(buffer);
		ft_strlgcpy(statix, &buffer[npoint], (BUFFER_SIZE + 1));
		buffer[npoint] = '\0';
		line = ft_strlgjoin(line, buffer, r_l);
		if (readed == 0)
		{
			ft_bzero(statix, (BUFFER_SIZE + 1));
			break ;
		}
	}
	return (line);
}

static char	*locline(char *statix, int *r_l)
{
	size_t	i;
	char	*line;

	if (!statix)
		return (NULL);
	i = 0;
	while (statix[i] && statix[i] != '\n')
		i++;
	i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, statix, i);
	line[i] = '\0';
	if (i > 0 && line[i - 1] == '\n')
		*r_l = i - 1;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	statix[BUFFER_SIZE + 1];
	char		*line;
	int			r_l;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	r_l = -1;
	line = locline(statix, &r_l);
	if (!line)
		return (NULL);
	ft_strlgcpy(statix, &statix[r_l + 1], (BUFFER_SIZE + 1));
	line = extracte_line(line, statix, &r_l, fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
