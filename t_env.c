/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 23:45:41 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/20 16:47:28 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		exit(EXIT_FAILURE);
	env->key = 0;
	env->value = 0;
	return (env);
}
