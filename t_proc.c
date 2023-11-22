/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_proc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:54:35 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/22 22:45:52 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_proc	*ft_new_proc(void)
{
	t_proc	*proc;

	proc = (t_proc *)malloc(sizeof(t_proc));
	if (!proc)
		exit(EXIT_FAILURE);
	proc->default_fdtype[READ_FD] = FDTYPE_STD;
	proc->default_fdtype[WRITE_FD] = FDTYPE_STD;
	proc->absolute_path = 0;
	proc->args = 0;
	proc->redir_list = ft_new_list();
	return (proc);
}

void	ft_del_proc(void *content)
{
	t_proc	*proc;

	proc = (t_proc *)content;
	two_d_free((void **)(proc->args));
	ft_list_clear(proc->redir_list, ft_del_redir);
	free(proc);
}
