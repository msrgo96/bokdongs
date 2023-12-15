/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 08:53:56 by moson             #+#    #+#             */
/*   Updated: 2023/12/11 08:53:57 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins/builtins.h"

void	dup2_and_close(int fd1, int fd2);
int		open_and_dup2_redir_return(t_redir *redir);

//	If error, exit(ERR_OPEN_FAILED, ERR_CLOSE_FAILED, ERR_DUP2_FAILED)
//	return 
//	**** WARNING: PRINT_ERROR WITH RETURN MUST BE HANDLED ****
int	set_io_fd_single_cmd(t_sh_data *sh_data, t_list *proc_list, int proc_num)
{
	t_proc	*proc;
	t_node	*redir_node;
	t_redir	*redir;
	int		open_and_dup2_res;

	proc = (t_proc *)(ft_listget(proc_list, proc_num)->content);
	if (proc->default_fdtype[READ_FD] == FDTYPE_PIPE)
		dup2_and_close(sh_data->fd_pipe[proc_num - 1][PIPE_READ], STDIN_FILENO);
	if (proc->default_fdtype[WRITE_FD] == FDTYPE_PIPE)
		dup2_and_close(sh_data->fd_pipe[proc_num][PIPE_WRITE], STDOUT_FILENO);
	redir_node = ft_listget(proc->redir_list, 0);
	while (redir_node != NULL)
	{
		redir = (t_redir *)(redir_node->content);
		open_and_dup2_res = open_and_dup2_redir_return(redir);
		if (open_and_dup2_res != SUCCESS)
			return (open_and_dup2_res);
		redir_node = redir_node->next;
	}
	return (SUCCESS);
}
