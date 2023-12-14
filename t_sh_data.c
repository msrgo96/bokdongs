/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_sh_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:47:22 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/14 17:50:18 by jooahn           ###   ########.fr       */
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
	return (sh_data);
}
