/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:58:54 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/16 15:25:45 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_del_node(t_node *node, void (*del)(void *))
{
	if (node == 0)
		return ;
	del(node->content);
	free(node);
	node = 0;
}
