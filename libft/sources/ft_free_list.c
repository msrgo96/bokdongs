/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 00:58:12 by jooahn            #+#    #+#             */
/*   Updated: 2023/10/25 01:14:52 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_list(t_list *list)
{
	t_node	*node;
	t_node	*temp;

	if (!list)
		return ;
	node = list->head;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
}

void	ft_free_list_with_content(t_list *list)
{
	t_node	*node;
	t_node	*temp;

	if (!list)
		return ;
	node = list->head;
	while (node)
	{
		temp = node->next;
		free(node->content);
		free(node);
		node = temp;
	}
}
