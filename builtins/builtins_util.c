/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:10:46 by moson             #+#    #+#             */
/*   Updated: 2023/11/21 04:10:47 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

//	Return arguments length
//	If args is NULL, return 0
int	get_args_len(char **args)
{
	int	len;

	if (args == NULL)
		return (0);
	len = 0;
	while (args[len] != NULL)
		len++;
	return (len);
}

//								return (int)		*res
//	If error				|	FT_FALSE		|	Undefined
//	If not exist			|	FT_TRUE			|	NULL
//	If searched				|	FT_TRUE			|	address
//	Dup check: NO
int	search_env_content(t_list *env_list, char *key, t_node	**res)
{
	t_node	*node;
	t_env	*content;

	if (env_list == NULL)
		return (FT_FALSE);
	node = env_list->head;
	while (node != NULL)
	{
		content = (t_env *)node->content;
		if (content == NULL || content->key == NULL)
			return (FT_FALSE);
		if (strncmp(content->key, key, ft_strlen(key) + 1) == 0)
		{
			*res = node;
			return (FT_TRUE);
		}
		node = node->next;
	}
	*res = NULL;
	return (FT_TRUE);
}
