/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:34:43 by moson             #+#    #+#             */
/*   Updated: 2023/11/18 16:34:44 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

int	search_env_content(t_list *env_list, char *key, t_node	**res);

static int	print_export_err(const int errno_export)
{
	char	*str;

	if (errno_export == EXPORT_NULPTR)
		str = EXPORT_NULPTR_MSG;
	else if (errno_export == EXPORT_UNKNOWN)
		str = EXPORT_UNKNOWN_MSG;
	else
		str = UNKNOWN_MSG;
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (errno_export);
}

int	export_builtin(t_sh_data *sh_data, t_proc *proc)
{
	t_node	*node;
	int		search_res;

	if (sh_data == NULL || sh_data->env_list == NULL)
		return (print_export_err(EXPORT_NULPTR));
	search_res = search_env_content(sh_data->env_list, proc->args[1], &node);
	if (search_res == FT_FALSE)
		return (print_export_err(EXPORT_UNKNOWN));
	if (node != NULL)
	{
		//	already exist: free node
	}
	//	ex) proc.args[1] = "TEST=asdf=123"
	//	key:	"TEST"
	//	value:	"asdf=123"
	return (EXIT_SUCCESS);
}
