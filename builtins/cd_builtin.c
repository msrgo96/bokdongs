/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:04:26 by moson             #+#    #+#             */
/*   Updated: 2023/11/28 23:00:14 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

int	get_args_len(char **args);

//	Return errno_chdir
static int	print_cd_err(const int errno_chdir)
{
	char	*str;

	str = strerror(errno_chdir);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (errno_chdir);
}

//	Return exit code of chdir()
int	cd_builtin(t_sh_data *sh_data, t_proc *proc)
{
	int	args_len;
	int	errno_chdir;

	(void)sh_data;
	args_len = get_args_len(proc->args);
	if (args_len == 0 || args_len == 1)
		errno_chdir = 0;
	else if (1 < args_len)
	{
		errno_chdir = 0;
		if (chdir(proc->args[1]) == -1)
		{
			errno_chdir = errno;
			errno_chdir = print_cd_err(errno_chdir);
		}
	}
	else
		errno_chdir = print_cd_err(EINVAL);
	return (errno_chdir);
}
