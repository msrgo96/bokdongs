/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:35:00 by moson             #+#    #+#             */
/*   Updated: 2023/11/18 16:35:01 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

static int	print_env_err(const int errno_env)
{
	char	*str;

	if (errno_env == ENV_NULL_KEY)
		str = ENV_NULL_KEY_MSG;
	else if (errno_env == ENV_INVAL_ARG)
		str = ENV_INVAL_ARG_MSG;
	else if (errno_env == ENV_NULPTR)
		str = ENV_NULPTR_MSG;
	else
		str = UNKNOWN_MSG;
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (errno_env);
}

//	Return exit code one of below:
//	SUCCESS
//	ENV_NULL_KEY
//	ENV_NULPTR
//	ENV_INVAL_ARG
int	env_builtin(t_sh_data *sh_data, t_proc *proc)
{
	t_node	*node;
	t_env	*content;

	if (proc->args[1] != NULL)
		return (print_env_err(ENV_INVAL_ARG));
	if (sh_data == NULL || sh_data->env_list == NULL)
		return (print_env_err(ENV_NULPTR));
	node = sh_data->env_list->head;
	while (node != NULL)
	{
		content = (t_env *)node->content;
		if (content == NULL || content->key == NULL)
			return (print_env_err(ENV_NULL_KEY));
		if (content->value == NULL)
		{
			node = node->next;
			continue ;
		}
		else if (ft_strlen(content->value) == 0)
			ft_printf("%s=\n", content->key, content->value);
		else
			ft_printf("%s=%s\n", content->key, content->value);
		node = node->next;
	}
	return (SUCCESS);
}
