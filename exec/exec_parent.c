/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:16:07 by moson             #+#    #+#             */
/*   Updated: 2023/12/03 11:16:08 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	If close failed: exit(ERR_CLOSE_FAILED)
static void	close_unused_pipe(t_sh_data *sh_data, int proc_num)
{
	int	read_pipe_idx;
	int	write_pipe_idx;

	read_pipe_idx = proc_num - 1;
	write_pipe_idx = proc_num;
	if (read_pipe_idx != -1)
		if (close(sh_data->fd_pipe[read_pipe_idx][PIPE_READ]) == -1)
			exit(ERR_CLOSE_FAILED);
	if (write_pipe_idx != sh_data->proc_size - 1)
		if (close(sh_data->fd_pipe[write_pipe_idx][PIPE_WRITE]) == -1)
			exit(ERR_CLOSE_FAILED);
	return ;
}

void	exec_parent(t_sh_data *sh_data, t_list *proc_list, int proc_num)
{
	proc_list++;
	close_unused_pipe(sh_data, proc_num);
	return ;
}
