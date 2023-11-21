/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_proc_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:15:26 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/21 21:13:46 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_proc	*create_proc(t_list *sub_token_list);

t_list	*create_proc_list(t_list *token_list)
{
	t_list	*proc_list;
	t_list	*sub_token_list;
	t_node	*node;

	if (!token_list)
		return (0);
	proc_list = ft_new_list();
	sub_token_list = ft_new_list();
	node = token_list->head;
	while (node)
	{
		ft_list_append(sub_token_list, ft_new_node(node->content));
		if (((t_token *)node->content)->type == PIPE)
		{
			ft_list_append(proc_list, ft_new_node(create_proc(sub_token_list)));
			//ft_list_clear(sub_token_list, ft_del_token);
			sub_token_list = ft_new_list();
			ft_list_append(sub_token_list, ft_new_node(node->content));
		}
		node = node->next;
	}
	ft_list_append(proc_list, ft_new_node(create_proc(sub_token_list)));
	//ft_list_clear(sub_token_list, ft_del_token);
	return (proc_list);
}

static t_proc	*create_proc(t_list *sub_token_list)
{
	t_proc	*proc;
	t_node	*node;
	t_token	*token;
	t_list	*arg_list;
	t_list	*redir_list;

	proc = ft_new_proc();
	if (((t_token *)sub_token_list->head->content)->type == PIPE)
		proc->default_fdtype[READ_FD] = FDTYPE_PIPE;
	if (((t_token *)sub_token_list->tail->content)->type == PIPE)
		proc->default_fdtype[WRITE_FD] = FDTYPE_PIPE;
	arg_list = ft_new_list();
	redir_list = ft_new_list();
	node = sub_token_list->head;
	while (node)
	{
		token = ((t_token *)node->content);
		if (token->type == CMD)
			ft_list_append(arg_list, ft_new_node(token->value));
		else if (is_redirection(token->type))
		{
			t_redir *redir = ft_new_redir();
			redir->redir_type = get_redir_type(token->value);
			node = node->next;
			if (!node)
				break ;
			redir->filename = ((t_token *)node->content)->value;
			ft_list_append(redir_list, ft_new_node(redir));
		}
		node = node->next;
	}
	proc->args = (char **)ft_list_to_ptr(arg_list, ft_none);
	proc->redir_list = redir_list;
	return (proc);
}
