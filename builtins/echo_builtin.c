/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 05:04:47 by moson             #+#    #+#             */
/*   Updated: 2023/11/28 23:00:05 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

int	get_args_len(char **args);

//	Return 0
int	echo_builtin(t_sh_data *sh_data, t_proc *proc)
{
	int	args_len;
	int	cnt;
	int	is_option;

	(void)sh_data;
	args_len = get_args_len(proc->args);
	cnt = 1;
	is_option = FT_FALSE;
	if (1 < args_len && ft_strncmp("-n", proc->args[1], 3) == 0)
	{
		is_option = FT_TRUE;
		cnt++;
	}
	while (cnt < args_len)
	{
		ft_putstr_fd(proc->args[cnt], STDOUT_FILENO);
		cnt++;
		if (cnt < args_len)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (is_option == FT_FALSE)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
