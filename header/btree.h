/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:13:08 by rdomange          #+#    #+#             */
/*   Updated: 2024/12/27 10:13:09 by rdomange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

typedef struct s_btree
{
	void			*data;
	struct s_btree	*parent;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

/*
skiena
search
insert
delete
print
successor/predecessor descendant
find_min

piscine
create_node
apply in, suff, pre fix
insert item
search item
level count
apply by level
*/

#endif	//btree.h