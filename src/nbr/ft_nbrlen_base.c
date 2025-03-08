/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:27:43 by rdomange          #+#    #+#             */
/*   Updated: 2025/03/04 21:06:44 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrlen_base(long nbr, int base)
{
	int	i;

	if (base < 2)
		return (0);
	if (nbr == 0)
		return (1);
	i = 0;
	if (nbr < 0 && base == 10)
	{
		nbr *= -1;
		i++;
	}
	while (nbr >= base)
	{
		nbr /= base;
		i++;
	}
	return (i);
}
