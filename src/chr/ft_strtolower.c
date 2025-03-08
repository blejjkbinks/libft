/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:41:58 by rdomange          #+#    #+#             */
/*   Updated: 2024/04/07 15:27:43 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtolower(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}
