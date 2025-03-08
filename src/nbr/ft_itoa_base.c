/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:33:19 by rdomange          #+#    #+#             */
/*   Updated: 2025/03/05 14:33:21 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_base_len(unsigned long nbr, int base);

char	*ft_itoa_base(unsigned long nbr, int base)
{
	char	*ret;
	int		len;

	if (base < 2 || base > 16)
		return (NULL);
	if (nbr == 0)
		return (ft_strdup("0"));
	len = ft_itoa_base_len(nbr, base);
	ret = (char *)ft_malloc((len + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[len] = 0;
	while (nbr)
	{
		len--;
		if (nbr % base < 10)
			ret[len] = nbr % base + '0';
		else
			ret[len] = nbr % base - 10 + 'a';
		nbr /= base;
	}
	return (ret);
}

static int	ft_itoa_base_len(unsigned long nbr, int base)
{
	int	l;

	if (base < 2)
		return (0);
	if (nbr == 0)
		return (1);
	l = 0;
	while (nbr)
	{
		nbr /= base;
		l++;
	}
	return (l);
}
