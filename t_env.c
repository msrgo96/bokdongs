/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:45:41 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/13 16:24:15 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		exit_wrapper(ERR_MALLOC_FAILED, NULL);
	env->key = 0;
	env->value = 0;
	return (env);
}

void	ft_del_env(void *env)
{
	if (!env)
		return ;
	free(((t_env *)env)->key);
	free(((t_env *)env)->value);
	free(env);
}

char	*get_env_value(t_list *env_list, char *key)
{
	t_node	*node;

	if (!env_list || !key)
		return (0);
	node = env_list->head;
	while (node)
	{
		if (ft_str_is_same(((t_env *)node->content)->key, key))
			return (((t_env *)node->content)->value);
		node = node->next;
	}
	return (0);
}
