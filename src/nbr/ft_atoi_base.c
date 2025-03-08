/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:32:56 by rdomange          #+#    #+#             */
/*   Updated: 2025/03/05 14:32:58 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_base_skipsign(const char *str, int *i, int *s, int base);

unsigned long	ft_atoi_base(const char *str, int base)
{
	unsigned long	ret;
	unsigned long	prev;
	int				sign;
	int				i;

	if (!str || base < 2 || base > 16)
		return (0);
	if (ft_atoi_base_skipsign(str, &i, &sign, base))
		return (0);
	ret = 0;
	while (ft_hexoffset(str[i]))
	{
		prev = ret;
		ret *= base;
		ret += ft_hexoffset(str[i]);
		if (prev > ret)
			return (ULONG_MAX);
		i++;
	}
	if (sign == -1)
		return (ULONG_MAX - ret + 1);
	return (ret);
}

static int	ft_atoi_base_skipsign(const char *str, int *i, int *sign, int base)
{
	int	c;

	*i = 0;
	while (ft_isspace(str[*i]))
		(*i)++;
	*sign = +1;
	if (str[*i] == '+' || str[*i] == '-')
		if (str[(*i)++] == '-')
			*sign = -1;
	c = *i;
	while (str[c])
	{
		if (!(0 <= ft_hexoffset(str[c]) && ft_hexoffset(str[c]) < base))
			return (1);
		c++;
	}
	return (0);
}
