/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:23:22 by jooahn            #+#    #+#             */
/*   Updated: 2023/10/20 23:56:08 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_lstget(t_node *lst, int i)
{
	t_node	*node;

	if (!lst)
		return (0);
	node = lst;
	while (i-- > 0)
		node = node->next;
	return (node);
}
