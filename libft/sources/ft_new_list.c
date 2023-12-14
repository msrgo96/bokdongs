/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:04:37 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/14 20:43:26 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_new_list(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		exit(ERR_MALLOC);
	list->head = 0;
	list->tail = 0;
	return (list);
}

t_list	*ft_new_list_init(void *content)
{
	t_list	*list;

	list = ft_new_list();
	ft_list_append(list, ft_new_node(content));
	return (list);
}
