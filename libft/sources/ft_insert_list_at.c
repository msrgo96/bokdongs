/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_list_at.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:44:40 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/16 15:03:23 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 미완성
void	ft_insert_list_at(t_list *base, t_list *insert, int at)
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
	if (node->prv)
		node->prv->next = insert->head;
	insert->head->prv = node->prv;
	insert->tail->next = node;
	node->prv = insert->tail;
	free(insert);
}
