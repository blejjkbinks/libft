/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapital.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:45:10 by rdomange          #+#    #+#             */
/*   Updated: 2024/03/25 14:52:07 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcapital(char *str)
{
	int		i;

	i = 0;
	if (str)
		str[i] = ft_toupper(str[i]);
	while (str && str[i + 1])
	{
		i++;
		if (!ft_isalnum(str[i - 1]))
			str[i] = ft_toupper(str[i]);
		else
			str[i] = ft_tolower(str[i]);
	}
}
