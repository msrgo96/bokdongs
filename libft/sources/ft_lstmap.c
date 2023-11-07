/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:59:25 by jooahn            #+#    #+#             */
/*   Updated: 2023/10/25 01:49:39 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_node	*ft_lstmap(t_node *lst, void *(*f)(void *), void (*del)(void *))
{
	t_node	*head;
	t_node	*node;

	if (!lst)
		return (0);
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (0);
	head = node;
	while (lst->next)
	{
		node->content = f(lst->content);
		node->next = (t_node *)malloc(sizeof(t_node));
		if (!(node->next))
		{
			ft_lstclear(&head, del);
			return (0);
		}
		lst = lst->next;
		node = node->next;
	}
	node->content = f(lst->content);
	node->next = 0;
	return (head);
}
