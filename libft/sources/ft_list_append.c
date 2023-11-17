/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:02:30 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 16:02:52 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_append(t_list *list, t_node *new)
{
	if (!(list->head) || !(list->tail))
	{
		new->prv = 0;
		new->next = 0;
		list->head = new;
		list->tail = new;
		return ;
	}
	list->tail->next = new;
	new->prv = list->tail;
	new->next = 0;
	list->tail = new;
}

void	ft_list_append_front(t_list *list, t_node *new)
{
	if (!(list->head) || !(list->tail))
	{
		new->prv = 0;
		new->next = 0;
		list->head = new;
		list->tail = new;
		return ;
	}
	list->head->prv = new;
	new->prv = 0;
	new->next = list->head;
	list->head = new;
}
