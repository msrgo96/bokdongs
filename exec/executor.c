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

void	exec_parent(t_sh_data *sh_data, t_list *proc_list, int proc_num);
void	exec_child(t_sh_data *sh_data, t_list *proc_list, int proc_num);

// static int	has_child(t_sh_data *sh_data)
// {
// 	int	cnt;

// 	cnt = -1;
// 	while (++cnt < sh_data->proc_size)
// 		if (sh_data->child_pid[cnt] != 0)
// 			return (FT_TRUE);
// 	return (FT_FALSE);
// }

void	wait_all_child(t_sh_data *sh_data)
{
	int	pid;
	int	status;
	int	cnt;

	pid = wait(&status);
	//	TODO: EXIT BY SIG or not?
	while (pid != -1)
	{
		cnt = -1;
		while (++cnt < sh_data->proc_size)
			if (sh_data->child_pid[cnt] == pid)
				break ;
		sh_data->child_pid[cnt] = 0;
		sh_data->exit_status[cnt] = WEXITSTATUS(status);
		pid = wait(&status);
	}
	return ;
}

int	executor(t_sh_data *sh_data, t_list *proc_list)
{
	int	cnt;

	//	write_temp_heredoc_file();
	//	modify_heredoc_redir_type();
	cnt = -1;
	while (++cnt < sh_data->proc_size)
	{

		sleep(1);

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
	//	remove_temp_heredoc_file();
	wait_all_child(sh_data);	//	wait all child
	for (int i = 0; i < sh_data->proc_size; i++)
		ft_printf("child %d: exit with code %d\n", i, sh_data->exit_status[i]);
	//	return (sh_data->exit_status[sh_data->proc_size - 1]);
	return (0);
}
