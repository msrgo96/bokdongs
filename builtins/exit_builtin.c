/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:35:08 by moson             #+#    #+#             */
/*   Updated: 2023/11/18 16:35:09 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

static int	print_exit_err(const int errno_exit)
{
	char	*str;

	if (errno_exit == EXIT_NAN)
		str = EXIT_NAN_MSG;
	else
		str = UNKNOWN_MSG;
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (errno_exit);
}

//	ALWAYS EXIT()
//	exit code one of below:
//	SUCCESS (no args)
//	0 ~ 255
//	EXIT_NAN (255)
int	exit_builtin(t_sh_data *sh_data, t_proc *proc)
{
	int	exit_code;

	sh_data++;
	ft_printf("exit\n");
	if (proc->args == NULL || proc->args[0] == NULL \
	|| proc->args[1] == NULL)
		exit(SUCCESS);
	if (!ft_isinteger(proc->args[1]))
		exit(print_exit_err(EXIT_NAN));
	exit_code = ft_atoi(proc->args[1]);
	exit((unsigned char)exit_code);
}
