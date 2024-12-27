/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:01:43 by rdomange          #+#    #+#             */
/*   Updated: 2024/12/27 10:01:44 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

t_list	*ft_lstcreate_node(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstfind(t_list *lst, void *data);
int		ft_lstlen(t_list *lst);
int		ft_lstindex(t_list *lst, t_list *find);
//at
void	ft_lstadd_front(t_list **lst, t_list *add);
void	ft_lstadd_back(t_list **lst, t_list *add);
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);

//at, rev, merge, sort, sorted_ins, sorted_merge, print, remove
//double list, remove prev or make single/double separate???

#endif	//list.h