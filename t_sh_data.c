/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_sh_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:47:22 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/15 01:17:15 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sh_data	*ft_new_sh_data(char **envp)
{
	t_sh_data	*sh_data;

	sh_data = (t_sh_data *)malloc(sizeof(t_sh_data) * 1);
	if (sh_data == NULL)
		exit(ERR_MALLOC_FAILED);
	sh_data->env_list = convert_envp_to_env_list(envp);
	sh_data->fd_std[STDIN_FILENO] = dup(STDIN_FILENO);
	sh_data->fd_std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	sh_data->fd_std[STDERR_FILENO] = dup(STDERR_FILENO);
	sh_data->child_pid = 0;
	sh_data->exit_status = 0;
	sh_data->fd_pipe = 0;
	sh_data->proc_size = 0;
	sh_data->hdfile_list = 0;
	return (sh_data);
}
