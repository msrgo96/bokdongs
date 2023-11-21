/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:11:25 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/21 20:24:16 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_token_list(t_list *token_list, t_list *env_list)
{
	t_node	*node;
	t_token	*token;

	if (!token_list || !env_list)
		return ;
	node = token_list->head;
	while (node)
	{
		token = (t_token *)(node->content);
		token->value = expand_string(env_list, token->value, free);
		node = node->next;
	}
}
