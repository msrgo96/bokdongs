/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:05:16 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 16:05:17 by jooahn           ###   ########.fr       */
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
