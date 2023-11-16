/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_node_with_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:01:58 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/16 16:20:39 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_replace_node_with_list_util(t_list *base, t_list *insert, t_node *node);

void	ft_replace_node_with_list(t_list *base, t_list *insert, int at)
{
	t_node	*node;

	if (!base || !insert)
		return ;
	if (ft_list_is_empty(insert))
	{
		free(insert);
		return ;
	}
	if (ft_list_is_empty(base))
	{
		base->head = insert->head;
		base->tail = insert->tail;
		free(insert);
		return ;
	}
	node = ft_listget(base, at);
	ft_replace_node_with_list_util(base, insert, node);
	ft_del_node(node, free);
	free(insert);
}

static void	ft_replace_node_with_list_util(t_list *base, t_list *insert, t_node *node)
{
	insert->head->prv = node->prv;
	insert->tail->next = node->next;
	if (node->prv)
		node->prv->next = insert->head;
	if (node->next)
		node->next->prv = insert->tail;
	if (insert->head->prv == 0)
		base->head = insert->head;
	if (insert->tail->next == 0)
		base->tail = insert->tail;
}
