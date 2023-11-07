/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:58:12 by jooahn            #+#    #+#             */
/*   Updated: 2023/10/25 01:14:52 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstfree(t_node *lst)
{
	t_node	*node;
	t_node	*temp;

	node = lst;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
}
