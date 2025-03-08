/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 20:00:49 by rdomange          #+#    #+#             */
/*   Updated: 2025/03/05 16:28:40 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_atoa_base(const char *str, int src_b, int dst_b)
{
	char	*ret;
	int		neg;

	while (ft_isspace(*str))
		str++;
	neg = 0;
	if (*str == '-')
		neg = 1;
	ret = ft_itoa_base(ft_atoi_base(str, src_b), dst_b);
	if (neg && ret && ft_strcmp(ret, "0"))
	{
		ft_memmove(ret + 1, ret, ft_strlen(ret));
		ret[0] = '-';
	}
	return (ret);
}
