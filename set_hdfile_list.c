/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hdfilepath_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:22:14 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/06 23:22:19 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_hdfile_list_util(t_list *redir_list, t_list *hdfile_list);
static char	*create_filepath(void);

// return : heredoc 갯수
int	set_hdfile_list(t_list *proc_list, t_list *hdfile_list)
{
	t_node	*node;
	t_proc	*proc;
	int		heredoc_cnt;

	if (!proc_list)
		return (0);
	heredoc_cnt = 0;
	node = proc_list->head;
	while (node)
	{
		proc = ((t_proc *)node->content);
		heredoc_cnt += set_hdfile_list_util(proc->redir_list, hdfile_list);
		node = node->next;
	}
	return (heredoc_cnt);
}

static int	set_hdfile_list_util(t_list *redir_list, t_list *hdfile_list)
{
	t_node	*node;
	t_redir	*redir;
	int		heredoc_cnt;

	if (!redir_list)
		return (0);
	heredoc_cnt = 0;
	node = redir_list->head;
	while (node)
	{
		redir = ((t_redir *)node->content);
		if (redir->redir_type == HEREDOC)
		{
			ft_list_append(hdfile_list, ft_new_node(create_filepath()));
			heredoc_cnt++;
		}
		node = node->next;
	}
	return (heredoc_cnt);
}

static char	*create_filepath(void)
{
	const char	*format;
	static long	cnt;
	char		*filepath;

	format = "/tmp/heredoc_";
	filepath = ft_strjoin(format, ft_itoa(cnt++), ft_none, free);
	while (access(filepath, F_OK) != -1)
	{
		free(filepath);
		filepath = ft_strjoin(format, ft_itoa(cnt++), ft_none, free);
	}
	return (filepath);
}
