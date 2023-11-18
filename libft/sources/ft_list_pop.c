/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_pop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:03:13 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 16:06:21 by jooahn           ###   ########.fr       */
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
