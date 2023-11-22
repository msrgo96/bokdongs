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

int	*search_env_content(t_list *env_list, char *key, t_node	**res);

//	Return exit code one of below:
//	EXIT_SUCCESS 0
//	UNSET_NOTEXIST 0
//	UNSET_NULPTR 1
//	UNSET_UNKNOWN 2
int	unset_builtin(t_sh_data *sh_data, t_proc *proc)
{
	t_node	*node;
	int		search_res;

	if (sh_data == NULL || sh_data->envp_list == NULL)
		return (UNSET_UNKNOWN);
	search_res = search_env_content(sh_data->envp_list, proc->args[1], &node);
	if 	(search_res == FT_FALSE)
		return (UNSET_UNKNOWN);
	if (node == NULL)
		return (UNSET_NOTEXIST);
	//	SUCCESS
	ft_del_node_and_link(sh_data->envp_list, node, ft_del_env);
	return (EXIT_SUCCESS);
}
