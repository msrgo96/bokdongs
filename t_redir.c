/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:31:19 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/13 16:24:15 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_new_redir(void)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		exit_wrapper(ERR_MALLOC_FAILED, NULL);
	redir->filename = 0;
	redir->redir_type = 0;
	return (redir);
}

t_redir	*ft_new_redir_init(char *filename, int redir_type)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		exit_wrapper(ERR_MALLOC_FAILED, NULL);
	redir->filename = filename;
	redir->redir_type = redir_type;
	return (redir);
}

void	ft_del_redir(void *content)
{
	t_redir	*redir;

	redir = (t_redir *)content;
	free(redir->filename);
	free(content);
}

int	get_redir_type(char *value)
{
	if (ft_str_is_same(value, "<"))
		return (I_REDIR);
	if (ft_str_is_same(value, ">"))
		return (O_REDIR);
	if (ft_str_is_same(value, ">>"))
		return (A_REDIR);
	if (ft_str_is_same(value, "<<"))
		return (HEREDOC);
	return (-1);
}

int	is_redirection(int type)
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
