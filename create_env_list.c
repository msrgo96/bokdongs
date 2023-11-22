/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:32:37 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/22 22:01:29 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_env_list(char **envp)
{
	t_list	*env_list;
	t_env	*env;
	char	*line;
	int		separator_idx;
	int		value_len;

	if (!envp)
		return (0);
	env_list = ft_new_list();
	while (*envp)
	{
		line = *envp;
		env = ft_new_env();
		separator_idx = ft_str_find_chr(line, '=');
		if (separator_idx < 0)
			return (0);
		value_len = ft_strlen(line) - (separator_idx + 1);
		env->key = ft_substr(line, 0, separator_idx);
		env->value = ft_substr(line, separator_idx + 1, value_len);
		ft_list_append(env_list, ft_new_node(env));
		envp++;
	}
	return (env_list);
}
