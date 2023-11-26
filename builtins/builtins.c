/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 05:26:06 by moson             #+#    #+#             */
/*   Updated: 2023/11/15 05:26:08 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

//	Check proc->args[0] and specify builtin-function
//	If error return NULL
//	Returns builtin-function pointer
static void	*get_builtin_ptr(t_proc *proc)
{
	if (ft_strncmp("echo", proc->args[0], 5) == 0)
		return (echo_builtin);
	else if (ft_strncmp("cd", proc->args[0], 3) == 0)
		return (cd_builtin);
	else if (ft_strncmp("pwd", proc->args[0], 4) == 0)
		return (pwd_builtin);
	else if (ft_strncmp("export", proc->args[0], 7) == 0)
		return (export_builtin);
	else if (ft_strncmp("unset", proc->args[0], 6) == 0)
		return (unset_builtin);
	else if (ft_strncmp("env", proc->args[0], 4) == 0)
		return (env_builtin);
	else if (ft_strncmp("exit", proc->args[0], 5) == 0)
		return (exit_builtin);
	else
		return (NULL);
}

//	If proc is NOT a builtin, return "NOT_A_BUILTIN"
//
//	If single builtin return "builtin exit code (MUST NOT FORK)"
//	Else if PIPE, exit process
int	exec_builtin(t_sh_data *sh_data, t_proc *proc)
{
	int	(*builtin)(t_sh_data *, t_proc *);

	builtin = get_builtin_ptr(proc);
	if (builtin == NULL)
		return (NOT_A_BUILTIN);
	if (proc->default_fdtype[0] == FDTYPE_PIPE \
	|| proc->default_fdtype[1] == FDTYPE_PIPE)
		exit(builtin(sh_data, proc));
	else
		return (builtin(sh_data, proc));
}
