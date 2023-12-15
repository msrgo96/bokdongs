/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 00:32:02 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/15 00:33:18 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_hdfilename_util(t_list *redir_list, t_list *hdfile_list);

void	replace_hdfilename(t_list *proc_list, t_list *hdfile_list)
{
	t_node	*node;
	t_proc	*proc;

	if (!proc_list || !hdfile_list)
		return ;
	node = proc_list->head;
	while (node)
	{
		proc = ((t_proc *)node->content);
		replace_hdfilename_util(proc->redir_list, hdfile_list);
		node = node->next;
	}
}

void	heredoc_clear(t_list *hdfile_list)
{
	t_node	*node;
	char	*filepath;

	if (!hdfile_list)
		return ;
	node = hdfile_list->head;
	while (node)
	{
		filepath = ((char *)node->content);
		unlink(filepath);
		node = node->next;
	}
}

static void	replace_hdfilename_util(t_list *redir_list, t_list *hdfile_list)
{
	t_node	*node;
	t_redir	*redir;
	t_node	*hdfile;

	node = redir_list->head;
	hdfile = hdfile_list->head;
	while (node)
	{
		redir = ((t_redir *)node->content);
		if (redir->redir_type == HEREDOC)
		{
			free(redir->filename);
			redir->filename = ft_strdup(((char *)hdfile->content));
			redir->redir_type = I_REDIR;
			hdfile = hdfile->next;
		}
		node = node->next;
	}
}
