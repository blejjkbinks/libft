/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:15:22 by rdomange          #+#    #+#             */
/*   Updated: 2025/01/07 17:15:28 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst, char t)
{
	while (lst)
	{
		if (lst->data)
		{
			ft_printf("[");
			if (t == 's')
				ft_printf("%s", lst->data);
			if (t == 'n')
				ft_printf("%ld", *((long *)lst->data));
			ft_printf("]");
			if (lst->next && lst->next->data)
				ft_printf(",");
		}
		lst = lst->next;
	}
}
