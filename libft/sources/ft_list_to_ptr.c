/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:50:03 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/12 22:21:40 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_list_to_ptr(t_list *list, void (*del)(void *))
{
	void	**ptr;
	int		size;
	t_node	*node;
	int		i;

	size = ft_listsize(list);
	ptr = (void **)malloc(sizeof(void *) * (size + 1));
	if (!ptr)
		ft_exit_with_msg(ERR_MALLOC);
	ptr[size] = 0;
	node = list->head;
	i = 0;
	while (node)
	{
		ptr[i++] = ft_strdup(node->content);
		node = node->next;
	}
	ft_list_clear(list, del);
	return (ptr);
}
