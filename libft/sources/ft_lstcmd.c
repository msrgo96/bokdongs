/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:21:41 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/15 14:06:09 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*lst_poll(t_list *list)
{
	t_node	*target;

	if (lst_is_empty(list))
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

void	lst_add(t_list *list, t_node *new)
{
	if (!(list->tail) || !(list->head))
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
	// if (ft_lstsize(list->head) == 1)
	// 	list->head = new;
}

int	lst_is_empty(t_list *list)
{
	if (ft_lstsize(list->head) < 1)
		return (1);
	return (0);
}
