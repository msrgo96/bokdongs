/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:03:53 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 16:03:55 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// i가 리스트 크기보다 크면 마지막 node 반환
// i가 음수면 첫 번째 node 반환
// 첫 번째 요소가 0
t_node	*ft_listget(t_list *list, int i)
{
	t_node	*node;

	if (!list)
		return (0);
	if (i >= ft_listsize(list))
		return (list->tail);
	node = list->head;
	while (node && i-- > 0)
		node = node->next;
	return (node);
}
