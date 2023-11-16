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
	// else if (ft_strncmp("cd", proc->args[0], 3) == 0)

	// else if (ft_strncmp("pwd", proc->args[0], 4) == 0)

	// else if (ft_strncmp("export", proc->args[0], 7) == 0)

	// else if (ft_strncmp("unset", proc->args[0], 6) == 0)

	// else if (ft_strncmp("env", proc->args[0], 4) == 0)

	// else if (ft_strncmp("exit", proc->args[0], 5) == 0)

	return (NULL);
}

int	exec_builtin(t_proc *proc)
{
	int	(*builtin)(t_proc *);

	builtin = get_builtin_ptr(proc);

}
