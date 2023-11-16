/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 00:43:05 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/16 11:52:40 by jooahn           ###   ########.fr       */
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
