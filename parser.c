/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:15:32 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/15 00:08:01 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;
static int	print_error(int error_code);
static int	is_empty_string(char *str);
static void	remove_empty_token(t_list *token_list);

/*
문법 체크(quote, syntax) && 토큰화 후 proc_list로 만들어 반환
return : process list
빈 문자열 or 공백으로만 이루어지면 리턴 0
*/
t_list	*parser(char *input, t_list *env_list)
{
	t_list	*token_list;
	t_list	*proc_list;

	if (check_quote(input) != SUCCESS)
	{
		g_exit_code = print_error(ERR_QUOTE);
		return (0);
	}
	token_list = tokenizer(input);
	if (!token_list)
	{
		g_exit_code = SUCCESS;
		return (0);
	}
	if (check_syntax(token_list) != SUCCESS)
	{
		g_exit_code = print_error(ERR_SYNTAX);
		ft_list_clear(token_list, ft_del_token);
		return (0);
	}
	expand_string_iter(token_list, env_list, expand_string, free);
	remove_empty_token(token_list);
	proc_list = generate_proc_list(token_list);
	ft_list_clear(token_list, ft_del_token);
	return (proc_list);
}

static void	remove_empty_token(t_list *token_list)
{
	t_token	*token;
	t_node	*node;
	t_node	*next;

	node = token_list->head;
	while (node)
	{
		next = node->next;
		token = ((t_token *)node->content);
		if (is_empty_string(token->value))
			ft_del_node_and_link(token_list, node, ft_del_token);
		node = next;
	}
}

static int	is_empty_string(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	print_error(int error_code)
{
	prt_err_entrance(error_code);
	printf("\n");
	return (error_code);
}
