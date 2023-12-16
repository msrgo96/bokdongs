/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:34:43 by moson             #+#    #+#             */
/*   Updated: 2023/12/15 19:36:55 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

int	search_env_content(t_list *env_list, char *key, t_node	**res);
int	ft_has_forbidden_keyname(char *str);

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

//	231216 18:08	If invalid key or value or error, return NULL
static t_env	*set_env(char *arg)
{
	t_env	*env;
	int		idx;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (NULL);
	env = ft_new_env();
	idx = ft_str_find_chr(arg, '=');
	if (idx == -1)
		idx = ft_strlen(arg);
	env->key = ft_substr(arg, 0, idx);
	if (arg[idx] != '\0')
		env->value = ft_substr(arg, idx + 1, ft_strlen(arg) - idx - 1);
	if (ft_has_forbidden_keyname(&env->key[1]))
	{
		ft_del_env(env);
		return (NULL);
	}
	return (env);
}

static int	export_no_args(t_sh_data *sh_data)
{
	t_node	*node;
	t_env	*content;

	if (sh_data == NULL || sh_data->env_list == NULL)
		return (print_export_err(EXPORT_NULPTR));
	node = sh_data->env_list->head;
	while (node != NULL)
	{
		content = (t_env *)node->content;
		if (content == NULL || content->key == NULL)
			return (print_export_err(EXPORT_NULPTR));
		ft_printf("declare -x ");
		if (content->value == NULL)
			ft_printf("%s\n", content->key);
		else
			ft_printf("%s=\"%s\"\n", content->key, content->value);
		node = node->next;
	}
	return (SUCCESS);
}

static int	export_for_an_item(t_sh_data *sh_data, t_env *env)
{
	t_node	*node;
	int		search_res;

	search_res = search_env_content(sh_data->env_list, env->key, &node);
	if (search_res == FT_FALSE)
	{
		ft_del_env(env);
		return (print_export_err(EXPORT_UNKNOWN));
	}
	if (node != NULL)
	{
		if (((t_env *)node->content)->value != NULL && env->value == NULL)
			return (SUCCESS);
		ft_del_node_and_link(sh_data->env_list, node, ft_del_env);
	}
	ft_list_append(sh_data->env_list, ft_new_node(env));
	return (SUCCESS);
}

int	export_builtin(t_sh_data *sh_data, t_proc *proc)
{
	int		cnt;
	int		has_error;
	int		tmp_ret;
	t_env	*env;

	if (sh_data == NULL || sh_data->env_list == NULL)
		return (print_export_err(EXPORT_NULPTR));
	if (proc->args[1] == NULL)
		return (export_no_args(sh_data));
	cnt = 0;
	has_error = 0;
	while (proc->args[++cnt] != NULL)
	{
		env = set_env(proc->args[cnt]);
		if (env == NULL)
		{
			print_export_err(EXPORT_FORMAT);
			has_error = EXPORT_FORMAT;
			continue ;
		}
		tmp_ret = export_for_an_item(sh_data, env);
		if (tmp_ret != 0)
			has_error = tmp_ret;
	}
	return (has_error);
}
