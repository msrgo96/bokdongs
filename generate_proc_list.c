/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_proc_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:15:26 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/14 23:01:33 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_proc	*generate_proc(t_list *sub_token_list);
static void		set_fd_type(t_list *sub_token_list, t_proc *proc);

/*
generate process list from token list
return : process list
*/
t_list	*generate_proc_list(t_list *token_list)
{
	t_list	*proc_list;
	t_list	*sub_list;
	t_node	*node;

	if (ft_list_is_empty(token_list))
		return (0);
	proc_list = ft_new_list();
	sub_list = ft_new_list();
	node = token_list->head;
	while (node)
	{
		ft_list_append(sub_list, ft_new_node(node->content));
		if (((t_token *)node->content)->type == PIPE)
		{
			ft_list_append(proc_list, ft_new_node(generate_proc(sub_list)));
			ft_list_clear(sub_list, ft_none);
			sub_list = ft_new_list_init(node->content);
		}
		node = node->next;
	}
	ft_list_append(proc_list, ft_new_node(generate_proc(sub_list)));
	ft_list_clear(sub_list, ft_none);
	return (proc_list);
}

static t_proc	*generate_proc(t_list *sub_list)
{
	t_proc	*proc;
	t_node	*node;
	t_token	*token;
	t_list	*arg_list;

	proc = ft_new_proc();
	set_fd_type(sub_list, proc);
	arg_list = ft_new_list();
	node = sub_list->head;
	while (node)
	{
		token = (t_token *)(node->content);
		if (token->type == CMD)
			ft_list_append(arg_list, ft_new_node(ft_strdup(token->value)));
		else if (is_redirection(token->type) && node->next)
		{
			node = node->next;
			ft_list_append(proc->redir_list, ft_new_node(\
			ft_new_redir_init(ft_strdup(((t_token *)node->content)->value) \
			, get_redir_type(token->value))));
		}
		node = node->next;
	}
	proc->args = (char **)ft_list_to_ptr(arg_list, free);
	return (proc);
}

static void	set_fd_type(t_list *sub_list, t_proc *proc)
{
	t_token	*head_token;
	t_token	*tail_token;

	head_token = ((t_token *)sub_list->head->content);
	tail_token = ((t_token *)sub_list->tail->content);
	if (head_token->type == PIPE)
		proc->default_fdtype[READ_FD] = FDTYPE_PIPE;
	if (tail_token->type == PIPE)
		proc->default_fdtype[WRITE_FD] = FDTYPE_PIPE;
}
