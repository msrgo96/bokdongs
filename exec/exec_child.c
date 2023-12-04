/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:16:14 by moson             #+#    #+#             */
/*   Updated: 2023/12/03 11:16:15 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_and_dup2_redir(t_redir *redir);

//	If close failed: exit(ERR_CLOSE_FAILED)
static void	close_unused_pipe(t_sh_data *sh_data, int proc_num)
{
	int	read_pipe_idx;

	read_pipe_idx = proc_num;
	if (read_pipe_idx != proc_num - 1)
		if (close(sh_data->fd_pipe[read_pipe_idx][PIPE_READ]) == -1)
			exit(ERR_CLOSE_FAILED);
	return ;
}

static void	set_io_fd(t_sh_data *sh_data, t_list *proc_list, int proc_num)
{
	t_proc	*proc;
	t_node	*redir_node;
	t_redir	*redir;
	int		fd;

	proc = (t_proc *)(ft_listget(proc_list, proc_num)->content);
	redir_node = (t_redir *)(ft_listget(proc->redir_list, 0));
	while (redir_node != NULL)
	{
		redir = (t_redir *)(redir_node->content);
		open_and_dup2_redir(redir);
		//	If pipe, update STD I/O with proper pipe fd
		redir_node = redir_node->next;
	}
}

void	exec_child(t_sh_data *sh_data, t_list *proc_list, int proc_num)
{
	close_unused_pipe(sh_data, proc_num);
	set_io_fd(sh_data, proc_list, proc_num);
	//	set absolute path (malloc)
	//	excute_proc
	//	if excute failed: exit with error code
	return ;
}
