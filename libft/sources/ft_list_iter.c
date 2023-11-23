/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:03:01 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/23 18:17:57 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_iter(t_list *list, void (*f)(void *))
{
	t_node	*node;

	if (!list)
		return ;
	node = list->head;
	while (node)
	{
		f(node->content);
		node = node->next;
	}
}

// content에 f()를 적용시킨 결과를 content에 재대입
t_list	*ft_list_iter_reassign(t_list *list, void *(*f)(void *))
{
	t_node	*node;

	if (!list)
		return (list);
	node = list->head;
	while (node)
	{
		node->content = f(node->content);
		node = node->next;
	}
	return (list);
}
