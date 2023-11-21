/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_proc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:54:35 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/21 20:31:36 by jooahn           ###   ########.fr       */
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
	proc->redir_list = 0;
	return (proc);
}
