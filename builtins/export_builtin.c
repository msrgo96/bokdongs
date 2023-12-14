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
int	env_builtin(t_sh_data *sh_data, t_proc *proc);

static int	print_export_err(const int errno_export)
{
	char	*str;

	if (errno_export == EXPORT_NULPTR)
		str = EXPORT_NULPTR_MSG;
	else if (errno_export == EXPORT_UNKNOWN)
		str = EXPORT_UNKNOWN_MSG;
	else if (errno_export == EXPORT_FORMAT)
		str = EXPORT_FORMAT_MSG;
	else
		str = UNKNOWN_MSG;
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (errno_export);
}

//	Return exit code one of below:
//	SUCCESS
//	EXPORT_NULPTR
//	EXPORT_UNKNOWN
//	EXPORT_FORMAT
int	export_builtin(t_sh_data *sh_data, t_proc *proc)
{
	t_node	*node;
	t_env	*env;
	int		search_res;
	int		separator_idx;
	int		value_len;

	if (sh_data == NULL || sh_data->env_list == NULL)
		return (print_export_err(EXPORT_NULPTR));
	if (proc->args[1] == NULL)
	{
		env_builtin(sh_data, proc);
		return (SUCCESS);
	}
	separator_idx = ft_str_find_chr(proc->args[1], '=');
	if (separator_idx < 0)
		return (print_export_err(EXPORT_FORMAT));
	env = ft_new_env();
	value_len = ft_strlen(proc->args[1]) - (separator_idx + 1);
	env->key = ft_substr(proc->args[1], 0, separator_idx);
	env->value = ft_substr(proc->args[1], separator_idx + 1, value_len);
	search_res = search_env_content(sh_data->env_list, env->key, &node);
	if (search_res == FT_FALSE)
	{
		ft_del_env(env);
		return (print_export_err(EXPORT_UNKNOWN));
	}
	if (node != NULL)
		ft_del_node_and_link(sh_data->env_list, node, ft_del_env);
	ft_list_append(sh_data->env_list, ft_new_node(env));
	return (SUCCESS);
}
