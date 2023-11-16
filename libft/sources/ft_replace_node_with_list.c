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

static void	link_list_at_node(t_list *base, t_list *sub, t_node *node);

void	ft_replace_node_with_list(t_list *base, t_list *sub, t_node *node)
{
	if (!base || !sub)
		return ;
	if (ft_list_is_empty(sub))
	{
		free(sub);
		return ;
	}
	if (ft_list_is_empty(base))
	{
		base->head = sub->head;
		base->tail = sub->tail;
		free(sub);
		return ;
	}
	link_list_at_node(base, sub, node);
	ft_del_node(node, free);
	free(sub);
}

static void	link_list_at_node(t_list *base, t_list *sub, t_node *node)
{
	sub->head->prv = node->prv;
	sub->tail->next = node->next;
	if (node->prv)
		node->prv->next = sub->head;
	if (node->next)
		node->next->prv = sub->tail;
	if (sub->head->prv == 0)
		base->head = sub->head;
	if (sub->tail->next == 0)
		base->tail = sub->tail;
}
