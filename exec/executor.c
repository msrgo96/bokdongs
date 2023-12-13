/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:00:42 by moson             #+#    #+#             */
/*   Updated: 2023/11/30 13:00:43 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../builtins/builtins.h"

void	*get_builtin_ptr(t_proc *proc);

void	exec_parent(t_sh_data *sh_data, t_list *proc_list, int proc_num);
void	exec_child(t_sh_data *sh_data, t_list *proc_list, int proc_num);
void	set_io_fd(t_sh_data *sh_data, t_list *proc_list, int proc_num);
char	*get_absolute_path(t_sh_data *sh_data, char *cmd);
char	**get_envp_origin(t_list *env_list);
void	restore_io_fd(t_sh_data *sh_data);
int		set_io_fd_single_cmd(t_sh_data *sh_data, t_list *proc_list, int proc_num);

void	wait_all_child(t_sh_data *sh_data, t_list *proc_list)
{
	int		pid;
	int		status;
	int		cnt;

	proc_list++;
	pid = wait(&status);
	while (pid != -1)
	{
		cnt = -1;
		while (++cnt < sh_data->proc_size)
			if (sh_data->child_pid[cnt] == pid)
				break ;
		sh_data->child_pid[cnt] = 0;
		sh_data->exit_status[cnt] = WEXITSTATUS(status);
		if (WIFSIGNALED(status) != 0)
			sh_data->exit_status[cnt] = SIGNAL_OFFSET + WTERMSIG(status);
		pid = wait(&status);
	}
	return ;
}

static void	exec_single(t_sh_data *sh_data, t_proc *proc)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	proc->absolute_path = get_absolute_path(sh_data, proc->args[0]);
	if (proc->absolute_path == NULL)
		exit(ERR_CMD_NOT_FOUND);
	if (access(proc->absolute_path, X_OK) == -1)
		exit(ERR_PERM_DENIED);
	if (execve(proc->absolute_path, proc->args, get_envp_origin(sh_data->env_list)) == -1)
		exit(ERR_EXECVE_FAILED);
	return ;
}

static int	single_cmd(t_sh_data *sh_data, t_list *proc_list)
{
	t_proc	*proc;
	int		set_io_res;

	proc = (t_proc *)(ft_listget(proc_list, 0)->content);
	set_io_res = set_io_fd_single_cmd(sh_data, proc_list, 0);
	if (set_io_res != SUCCESS)
		return (set_io_res);
	sh_data->child_pid[0] = 0;
	sh_data->exit_status[0] = exec_builtin(sh_data, proc);
	if (sh_data->exit_status[0] == NOT_A_BUILTIN)
	{
		sh_data->child_pid[0] = fork();
		if (sh_data->child_pid[0] == 0)
			exec_single(sh_data, proc);
	}
	heredoc_clear(sh_data->hdfile_list);
	wait_all_child(sh_data, proc_list);
	restore_io_fd(sh_data);
	return (sh_data->exit_status[0]);
}

static int	multi_cmds(t_sh_data *sh_data, t_list *proc_list)
{
	int	cnt;

	cnt = -1;
	while (++cnt < sh_data->proc_size)
	{
		if (cnt != sh_data->proc_size - 1)
			if (pipe(sh_data->fd_pipe[cnt]) == -1)
				exit(ERR_PIPE_FAILED);
		sh_data->child_pid[cnt] = fork();
		if (sh_data->child_pid[cnt] == -1)
			exit(ERR_FORK_FAILED);
		if (0 < sh_data->child_pid[cnt])
			exec_parent(sh_data, proc_list, cnt);
		else
			exec_child(sh_data, proc_list, cnt);
	}
	heredoc_clear(sh_data->hdfile_list);
	wait_all_child(sh_data, proc_list);
	return (sh_data->exit_status[sh_data->proc_size - 1]);
}

int	executor(t_sh_data *sh_data, t_list *proc_list)
{
	if (set_hdfile_list(proc_list, sh_data->hdfile_list) > 0)
	{
		heredoc(proc_list, sh_data);
		
		replace_filename(proc_list, sh_data->hdfile_list);
	}
	if (sh_data->proc_size == 1)
		return (single_cmd(sh_data, proc_list));
	else
		return (multi_cmds(sh_data, proc_list));
}
