/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:39:56 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/07 16:13:59 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtoupper(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}
