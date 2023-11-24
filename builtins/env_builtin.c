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

	if (errno_env == ENV_NULPTR)
		str = ENV_NULPTR_MSG;
	else
		str = UNKNOWN_MSG;
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (errno_env);
}

//	Return exit code one of below:
//	EXIT_SUCCESS
//	ENV_NULPTR
int	env_builtin(t_sh_data *sh_data, t_proc *proc)
{
	t_node	*node;
	t_env	*content;

	proc++;
	if (sh_data == NULL || sh_data->env_list == NULL)
		return (print_env_err(ENV_NULPTR));
	node = sh_data->env_list->head;
	while (node != NULL)
	{
		content = (t_env *)node->content;
		if (content == NULL || content->key == NULL || content->value == NULL)
			return (print_env_err(ENV_NULPTR));
		ft_printf("%s=%s\n", content->key, content->value);
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
