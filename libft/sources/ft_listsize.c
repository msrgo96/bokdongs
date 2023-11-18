/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:04:25 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 16:04:26 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_listsize(t_list *list)
{
	int		size;
	t_node	*node;

	if (!list)
		return (0);
	size = 0;
	node = list->head;
	while (node)
	{
		node = node->next;
		size++;
	}
	return (size);
}
