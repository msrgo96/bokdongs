/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_and_link.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:05:08 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/14 23:19:36 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_node_and_link(t_list *list, t_node *target, void (*del)(void *))
{
	t_node	*node;

	if (!list || !target)
		return ;
	node = list->head;
	while (node)
	{
		if (node == target)
		{
			if (target == list->head)
				list->head = target->next;
			if (target == list->tail)
				list->tail = target->prv;
			if (target->prv)
				target->prv->next = target->next;
			if (target->next)
				target->next->prv = target->prv;
			ft_del_node(node, del);
			return ;
		}
		node = node->next;
	}
}
