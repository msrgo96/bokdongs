/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:53:56 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/16 00:58:11 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **argv, char **envp, t_sh_data **sh_data)
{
	(void)argv;
	*sh_data = ft_new_sh_data(envp);
	signal(SIGQUIT, SIG_IGN);
}

void	print_newline_if_signaled(t_sh_data *sh_data)
{
	int	i;

	i = 0;
	while (i < sh_data->proc_size)
	{
		if (sh_data->exit_status[i] == SIGNAL_OFFSET + SIGINT \
		|| sh_data->exit_status[i] == SIGNAL_OFFSET + SIGQUIT)
		{
			write(1, "\n", 1);
			return ;
		}
		i++;
	}
}

void	clear_after_input(char *str, t_sh_data *sh_data, t_list *proc_list)
{
	ft_free((void **)&str);
	clear_proc_sh_data(sh_data);
	ft_list_clear(proc_list, ft_del_proc);
}

void	clear_shell(t_sh_data *sh_data)
{
	ft_list_clear(sh_data->env_list, ft_del_env);
	ft_free((void **)&sh_data);
}
