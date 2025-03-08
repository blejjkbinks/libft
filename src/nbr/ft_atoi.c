/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:25:33 by rdomange          #+#    #+#             */
/*   Updated: 2024/05/06 14:10:48 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_atoi_dec(const char *str);
static long	ft_atoi_hex(const char *s);

long	ft_atoi(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (!ft_strncmp("0x", &str[i], 2) || !ft_strncmp("0X", &str[i], 2))
		return (ft_atoi_hex(&str[i + 2]));
	else
		return (ft_atoi_dec(&str[i]));
}

static long	ft_atoi_dec(const char *str)
{
	long	ret;
	long	prev;
	int		sign;
	int		i;

	i = 0;
	sign = +1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	ret = 0;
	while (ft_isdigit(str[i]))
	{
		prev = ret;
		ret *= 10;
		ret += str[i] - '0';
		if (prev > ret && sign == +1)
			return (LONG_MAX);
		if (prev > ret && sign == -1)
			return (LONG_MIN);
		i++;
	}
	return (ret * sign);
}

static long	ft_atoi_hex(const char *str)
{
	long	ret;
	long	prev;
	int		i;

	i = 0;
	ret = 0;
	while (ft_hexoffset(str[i]))
	{
		prev = ret;
		ret *= 16;
		ret += str[i] - ft_hexoffset(str[i]);
		if (prev > ret)
			return (LONG_MAX);
		i++;
	}
	return (ret);
}
