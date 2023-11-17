/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:15:26 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 23:30:41 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_proc_list(t_list *token_list)
{
	t_list	*proc_list;
	t_proc	*proc;
	t_node	*node;

	if (!token_list)
		return ;
	proc_list = ft_new_list();
	node = token_list->head;
	while (node)
	{

		node = node->next;
	}
}
