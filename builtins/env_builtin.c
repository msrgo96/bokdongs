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

//	Return exit code one of below:
//	EXIT_SUCCESS
//	ENV_NULPTR
int	env_builtin(t_sh_data *sh_data, t_proc *proc)
{
	t_node	*node;
	t_env	*content;

	proc++;
	if (sh_data == NULL || sh_data->envp_list == NULL)
		return (ENV_NULPTR);
	node = sh_data->envp_list->head;
	while (node != NULL)
	{
		content = (t_env *)node->content;
		if (content == NULL || content->key == NULL || content->value == NULL)
			return (ENV_NULPTR);
		ft_printf("%s=%s\n", content->key, content->value);
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
