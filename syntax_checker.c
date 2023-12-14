/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:35:30 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/14 16:40:45 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_node_type(t_node *node);

/*
split str and wrap in token list
return : 따옴표 짝 맞으면 return SUCCESS,
짝 안맞으면 return ERR_QUOTE
*/
int	check_quote(char *input)
{
	int	i;
	int	in_quote[2];

	i = 0;
	in_quote[SINGLE] = 0;
	in_quote[DOUBLE] = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_quote[DOUBLE])
			in_quote[SINGLE] ^= 1;
		else if (input[i] == '\"' && !in_quote[SINGLE])
			in_quote[DOUBLE] ^= 1;
		i++;
	}
	if (in_quote[SINGLE] || in_quote[DOUBLE])
		return (ERR_QUOTE);
	return (SUCCESS);
}

/*
check syntax like "pipe comes first or last"
return : SUCCESS or ERR_SYNTAX
*/
int	check_syntax(t_list	*token_list)
{
	t_node	*cur;
	t_node	*next;

	if (ft_list_is_empty(token_list))
		return (SUCCESS);
	if (get_node_type(token_list->head) == PIPE \
	|| get_node_type(token_list->tail) != CMD)
		return (ERR_SYNTAX);
	cur = token_list->head;
	next = cur->next;
	while (cur && next)
	{
		if (is_redirection(get_node_type(cur)) \
		&& get_node_type(next) != CMD)
			return (ERR_SYNTAX);
		else if (get_node_type(cur) == PIPE \
		&& get_node_type(next) == PIPE)
			return (ERR_SYNTAX);
		cur = next;
		next = cur->next;
	}
	return (SUCCESS);
}

static int	get_node_type(t_node *node)
{
	return (((t_token *)(node->content))->type);
}
