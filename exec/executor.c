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
#include <errno.h>

//	If error exit minishell with ERR_PIPE_FAILED
static int	open_pipe(t_sh_data *sh_data)
{
	int	cnt;

	cnt = -1;
	while (++cnt < sh_data->proc_size - 1)
		if (pipe(sh_data->fd_pipe[cnt]) == -1)
			exit(ERR_PIPE_FAILED);
	return (SUCCESS);
}

//	DEPRECATED close_pipe()
/*
//	If error exit minishell with ERR_CLOSE_FAILED
//	To close ALL, set both ignore_r and ignore_w to -1
//	Not to close specified fd, set ignore_r or ignore_w
static int	close_pipe(t_sh_data *sh_data, int ignore_r, int ignore_w)
{
	int	cnt;

	cnt = -1;
	while (++cnt < sh_data->proc_size - 1)
	{
		if (cnt != ignore_r && close(sh_data->fd_pipe[cnt][PIPE_READ]) == -1)
			exit(ERR_CLOSE_FAILED);
		if (cnt != ignore_w && close(sh_data->fd_pipe[cnt][PIPE_WRITE]) == -1)
			exit(ERR_CLOSE_FAILED);
	}
	return (SUCCESS);
}
*/

int	executor(t_sh_data *sh_data, t_list *proc_list)
{
	int	cnt;

	//	write_temp_heredoc_file();
	//	modify_heredoc_redir_type();

	open_pipe(sh_data);
	cnt = -1;
	while (++cnt < sh_data->proc_size)
	{
		sh_data->child_pid[cnt] = fork();
		if (0 < sh_data->child_pid[cnt])
			exec_parent();
		else
			exec_child();
	}
	//	remove_temp_heredoc_file();
	// close_pipe(sh_data, -1, -1);	//	DEPRECATED
	//	wait all child
	//	return (sh_data->exit_status[sh_data->proc_size - 1]);
}
