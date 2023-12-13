/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:15:07 by moson             #+#    #+#             */
/*   Updated: 2023/12/13 00:20:38 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*malloc_exit_if_failed(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
		exit_wrapper(ERR_MALLOC_FAILED, NULL);
	return (res);
}

//	If malloc failed: exit(ERR_MALLOC_FAILED)
//	else return (SUCCESS)
int	set_proc_sh_data(t_sh_data *sh_data, t_list *proc_list)
{
	int	cnt;

	sh_data->proc_size = ft_listsize(proc_list);
	sh_data->fd_pipe = (int **)malloc_exit_if_failed(sizeof(int *) * sh_data->proc_size);
	cnt = -1;
	while (++cnt < sh_data->proc_size)
		sh_data->fd_pipe[cnt] = (int *)malloc_exit_if_failed(sizeof(int) * 2);
	sh_data->child_pid = (int *)malloc_exit_if_failed(sizeof(int) * sh_data->proc_size); // 수정
	cnt = -1;
	while (++cnt < sh_data->proc_size)
		sh_data->child_pid[cnt] = 0;
	sh_data->exit_status = (int *)malloc_exit_if_failed(sizeof(int) * sh_data->proc_size); // 수정
	cnt = -1;
	while (++cnt < sh_data->proc_size)
		sh_data->exit_status[cnt] = 0;
	sh_data->hdfile_list = ft_new_list();
	return (SUCCESS);
}

//	FREE all proc-data in sh_data with proc_size
//	**** WARNING: If sh_data->proc_size is undefined, cause SEGFAULT ****
void	clear_proc_sh_data(t_sh_data *sh_data)
{
	int	cnt;

	cnt = -1;
	while (++cnt < sh_data->proc_size)
		ft_free((void **)&(sh_data->fd_pipe[cnt]));
	free(sh_data->fd_pipe);
	sh_data->fd_pipe = NULL;
	ft_free((void *)&(sh_data->child_pid));
	ft_free((void *)&(sh_data->exit_status));
	sh_data->proc_size = -1;
	ft_list_clear(sh_data->hdfile_list, ft_none);
	sh_data->hdfile_list = NULL;
	return ;
}
