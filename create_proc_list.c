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

t_proc	*create_proc(t_list *token_list)
{
	t_proc	*proc;
	t_node	*node;
	t_token	*token;

	if (!token_list)
		return ;
	proc = ft_new_proc();
	node = token_list->head;
	while (!ft_list_is_empty(token_list))
	{
		node = ft_list_pop(token_list);
		token = ((t_token *)node->content);
		if (token->type == PIPE)
		{
			ft_del_node(node, ft_del_token);
			break ;
		}
		if (token->type == CMD)

	}
	return (proc);
}

void	
