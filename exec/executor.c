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
	int		cnt;
	pid_t	pid;

	//	write_temp_heredoc_file();
	//	modify_heredoc_redir_type();

	//	open ALL pipe
	cnt = -1;
	while (++cnt < sh_data->proc_size)
		if (pipe(sh_data->fd_pipe[cnt]) == -1)
			exit(ERR_PIPE_FAILED);
	cnt = -1;
	while (++cnt < sh_data->proc_size)
	{
		pid = fork();
		if (0 < pid)
			parent();
		else
			child();
	}
	//	remove_temp_heredoc_file();
	//	close
	//	wait all child
	//	return (sh_data->exit_status[sh_data->proc_size - 1]);
	return (0);	//	temp return
}
