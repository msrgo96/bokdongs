/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:35:30 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 22:31:31 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_node_type(t_node *node);
static int	is_redirection(int type);

int	check_quotes(char *input)
{
	int	i;
	int	in_quotes[2];

	i = 0;
	in_quotes[SINGLE] = 0;
	in_quotes[DOUBLE] = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_quotes[DOUBLE])
			in_quotes[SINGLE] ^= 1;
		else if (input[i] == '\"' && !in_quotes[SINGLE])
			in_quotes[DOUBLE] ^= 1;
		i++;
	}
	if (in_quotes[SINGLE] || in_quotes[DOUBLE])
		return (QUOTES_ERROR);
	return (VALID);
}

int	check_syntax(t_list	*token_list)
{
	t_node	*cur;
	t_node	*next;

	if (ft_list_is_empty(token_list))
		return (VALID);
	if (get_node_type(token_list->head) == PIPE \
	|| get_node_type(token_list->tail) != CMD)
		return (SYNTAX_ERROR);
	cur = token_list->head;
	next = cur->next;
	while (cur && next)
	{
		if (is_redirection(get_node_type(cur)) \
		&& get_node_type(next) != CMD)
			return (SYNTAX_ERROR);
		else if (get_node_type(cur) == PIPE \
		&& get_node_type(next) == PIPE)
			return (SYNTAX_ERROR);
		cur = next;
		next = cur->next;
	}
	return (VALID);
}

static int	get_node_type(t_node *node)
{
	return (((t_token *)(node->content))->type);
}

static int	is_redirection(int type)
{
	if (type == I_REDIR)
		return (1);
	if (type == O_REDIR)
		return (1);
	if (type == A_REDIR)
		return (1);
	if (type == HEREDOC)
		return (1);
	return (0);
}
