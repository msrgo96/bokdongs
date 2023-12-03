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

int	executor(t_sh_data *sh_data, t_list *proc_list)
{
	int	cnt;

	//	write_temp_heredoc_file();
	//	modify_heredoc_redir_type();

	cnt = -1;
	while (++cnt < sh_data->proc_size)
	{
		if (cnt != sh_data->proc_size - 1)
			if (pipe(sh_data->fd_pipe[cnt]) == -1)
				exit(ERR_PIPE_FAILED);
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
