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
void	dup2_and_close(int fd1, int fd2);

//	If close failed: exit (ERR_CLOSE_FAILED)
static void	close_unused_pipe(t_sh_data *sh_data, int proc_num)
{
	int	read_pipe_idx;

	read_pipe_idx = proc_num;
	if (read_pipe_idx != proc_num - 1)
		if (close(sh_data->fd_pipe[read_pipe_idx][PIPE_READ]) == -1)
			exit(ERR_CLOSE_FAILED);
	return ;
}

//	If error, exit(ERR_OPEN_FAILED, ERR_CLOSE_FAILED, ERR_DUP2_FAILED, ERR_FILE_NOT_EXIST, ERR_PERM_DENIED)
static void	set_io_fd(t_sh_data *sh_data, t_list *proc_list, int proc_num)
{
	t_proc	*proc;
	t_node	*redir_node;
	t_redir	*redir;

	proc = (t_proc *)(ft_listget(proc_list, proc_num)->content);
	if (proc->default_fdtype[READ_FD] == FDTYPE_PIPE)
		dup2_and_close(sh_data->fd_pipe[proc_num - 1][PIPE_READ], STDIN_FILENO);
	if (proc->default_fdtype[WRITE_FD] == FDTYPE_PIPE)
		dup2_and_close(sh_data->fd_pipe[proc_num][PIPE_WRITE], STDOUT_FILENO);
	redir_node = ft_listget(proc->redir_list, 0);
	while (redir_node != NULL)
	{
		redir = (t_redir *)(redir_node->content);
		open_and_dup2_redir(redir);
		redir_node = redir_node->next;
	}
	return ;
}

//	TODO:	TEMP
#include <fcntl.h>	//	for open()

void	exec_child(t_sh_data *sh_data, t_list *proc_list, int proc_num)
{
	close_unused_pipe(sh_data, proc_num);
	set_io_fd(sh_data, proc_list, proc_num);
	//	set absolute path (malloc):
	//	1. malloc [ '\0' ]: it is cmd but not exist || it is builtin
	//	2. malloc [ absolute path]: it is cmd and exist

	#pragma region WRITE_PROC_INFO_TXT
	//	TODO:	temp
	if (chdir("./exec") == -1)
	{
		ft_putendl_fd("chdir error", STDERR_FILENO);
		exit(1);
	}
	t_proc	*proc = (t_proc *)(ft_listget(proc_list, proc_num)->content);
	int		fd = open("info_proc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit (1);
	ft_putendl_fd("********\tproc info\t********", fd);
	ft_putstr_fd("absolute_path: ", fd);
	if (proc->absolute_path == NULL)
		ft_putendl_fd("(NULL)", fd);
	else
		ft_putendl_fd(proc->absolute_path, fd);
	for (int i = 0; proc->args[i] != NULL; i++)
	{
		ft_putstr_fd("args[", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("]: ", fd);
		ft_putendl_fd(proc->args[i], fd);
	}
	exit (0);
	//	TODO:	END TEMP
	#pragma endregion

	//	excute_proc
	//	if excute failed: exit with error code + close * free
	return ;
}
