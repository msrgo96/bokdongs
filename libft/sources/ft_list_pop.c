/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:21:41 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/15 14:06:09 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_list_pop(t_list *list)
{
	t_node	*target;

	if (ft_list_is_empty(list))
		return (NULL);
	target = list->head;
	list->head = list->head->next;
	if (list->head)
		list->head->prv = NULL;
	else
		list->tail = NULL;
	target->next = NULL;
	return (target);
}


