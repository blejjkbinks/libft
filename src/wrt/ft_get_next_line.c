/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:50:15 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/29 15:45:32 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_realloc_gnl(char *src, size_t *c);

char	*get_next_line(int fd)
{
	char	*ret;
	size_t	i;
	size_t	c;

	c = 16;
	i = 0;
	ret = (char *)ft_malloc(c * sizeof(char));
	while (ret && read(fd, &ret[i], 1) == 1)
	{
		if (ret[i] == '\n')
		{
			ret[i] = 0;
			return (ret);
		}
		ret[++i] = 0;
		if (i + 1 == c)
			ret = ft_realloc_gnl(ret, &c);
	}
	if (!i)
		return (ft_free(ret));
	return (ret);
}

static char	*ft_realloc_gnl(char *src, size_t *c)
{
	char	*dst;
	int		i;

	if (!src)
		return (NULL);
	*c *= 2;
	dst = (char *)ft_malloc(*c * sizeof(char));
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	free(src);
	return (dst);
}
