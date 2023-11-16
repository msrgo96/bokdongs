/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 05:04:47 by moson             #+#    #+#             */
/*   Updated: 2023/11/15 05:04:49 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

//	If error return ERR_CODE (const)
//	Note that: proc->args is NOT NULL, 
//	and proc->args[0] implies the command is "builtin-echo"
int	echo_builtin(t_proc *proc)
{
	int	cnt;
	int	is_option;

	cnt = 0;
	is_option = FT_FALSE;
	if (proc->args[1] != NULL && \
	ft_strncmp("-n", proc->args[1], 3) == 0)
	{
		cnt++;
		is_option = FT_TRUE;
	}
	while (proc->args[++cnt] != NULL)
		ft_printf("%s\n", proc->args[cnt]);
	if (is_option == FT_FALSE)
		ft_printf("\n");
	return (DEFAULT_EXIT);
}
