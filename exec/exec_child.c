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
#include "../builtins/builtins.h"

void	dup2_and_close(int fd1, int fd2);
char	*get_absolute_path(t_sh_data *sh_data, char *cmd);
char	**get_envp_origin(t_list *env_list);
void	open_and_dup2_redir_exit(t_redir *redir);

//	If close failed: exit (ERR_CLOSE_FAILED)
static void	close_unused_pipe(t_sh_data *sh_data, int proc_num)
{
	int	read_pipe_idx;

	read_pipe_idx = proc_num;
	if (read_pipe_idx != sh_data->proc_size - 1)
		if (close(sh_data->fd_pipe[read_pipe_idx][PIPE_READ]) == -1)
			exit_wrapper(ERR_CLOSE_FAILED, NULL);
	return ;
}

//	If error, exit(ERR_OPEN_FAILED, ERR_CLOSE_FAILED, ERR_DUP2_FAILED, ERR_FILE_NOT_EXIST, ERR_PERM_DENIED)
void	set_io_fd(t_sh_data *sh_data, t_list *proc_list, int proc_num)
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
		open_and_dup2_redir_exit(redir);
		redir_node = redir_node->next;
	}
	return ;
}

void	exec_child(t_sh_data *sh_data, t_list *proc_list, int proc_num)
{
	t_proc	*proc;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	proc = (t_proc *)(ft_listget(proc_list, proc_num)->content);
	close_unused_pipe(sh_data, proc_num);
	set_io_fd(sh_data, proc_list, proc_num);
	exec_builtin(sh_data, proc);
	proc->absolute_path = get_absolute_path(sh_data, proc->args[0]);
	if (execve(proc->absolute_path, proc->args, get_envp_origin(sh_data->env_list)) == -1)
		exit_wrapper(ERR_EXECVE_FAILED, NULL);
	return ;
}
