/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:34:52 by moson             #+#    #+#             */
/*   Updated: 2023/11/18 16:34:53 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

int	search_env_content(t_list *env_list, char *key, t_node	**res);

static int	print_unset_err(const int errno_unset)
{
	char	*str;

	if (errno_unset == UNSET_NULPTR)
		str = UNSET_NULPTR_MSG;
	else if (errno_unset == UNSET_UNKNOWN)
		str = UNSET_UNKNOWN_MSG;
	else
		str = UNKNOWN_MSG;
	ft_putstr_fd("unset: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (errno_unset);
}

//	Return exit code one of below:
//	SUCCESS
//	UNSET_NOTEXIST
//	UNSET_NULPTR
//	UNSET_UNKNOWN
int	unset_builtin(t_sh_data *sh_data, t_proc *proc)
{
	t_node	*node;
	int		search_res;

	if (sh_data == NULL || sh_data->env_list == NULL)
		return (print_unset_err(UNSET_NULPTR));
	search_res = search_env_content(sh_data->env_list, proc->args[1], &node);
	if (search_res == FT_FALSE)
		return (print_unset_err(UNSET_UNKNOWN));
	if (node == NULL)
		return (UNSET_NOTEXIST);
	ft_del_node_and_link(sh_data->env_list, node, ft_del_env);
	return (SUCCESS);
}
