/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_node_idx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:51:26 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/16 14:14:38 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_node_idx(t_list *list, t_node *target)
{
	t_node	*node;
	int		idx;

	if (!list)
		return (-1);
	node = list->head;
	idx = 0;
	while (node)
	{
		if (node == target)
			return (idx);
		node = node->next;
		idx++;
	}
	return (-1);
}
