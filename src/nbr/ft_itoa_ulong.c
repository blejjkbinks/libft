/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ulong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:25:38 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/16 11:35:58 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ulong_len(unsigned long n);

char	*ft_itoa_ulong(unsigned long nbr)
{
	char	*ret;
	int		len;

	if (nbr == 0)
		return (ft_strdup("0"));
	len = ft_ulong_len(nbr);
	ret = (char *)ft_malloc((len + 1) * sizeof(char));
	ret[len] = 0;
	while (nbr)
	{
		len--;
		ret[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (ret);
}

static int	ft_ulong_len(unsigned long n)
{
	int	l;

	l = 0;
	while (n)
	{
		l++;
		n /= 10;
	}
	return (l);
}
