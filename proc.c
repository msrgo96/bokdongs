/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:54:35 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 15:06:33 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_proc	*ft_new_proc(void)
{
	t_proc	*proc;

	proc = (t_proc *)malloc(sizeof(proc));
	if (!proc)
		exit(EXIT_FAILURE);
	proc->default_fdtype[0] = 0;
	proc->default_fdtype[1] = 0;
	proc->absolute_path = 0;
	proc->args = 0;
	proc->envp_list = 0;
	proc->redir_list = 0;
	return (proc);
}
