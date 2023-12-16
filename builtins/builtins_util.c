/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:10:46 by moson             #+#    #+#             */
/*   Updated: 2023/11/28 22:59:39 by ahn              ###   ########.fr       */
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
		if (ft_strncmp(content->key, key, ft_strlen(key) + 1) == 0)
		{
			*res = node;
			return (FT_TRUE);
		}
		node = node->next;
	}
	*res = NULL;
	return (FT_TRUE);
}

int	ft_has_forbidden_keyname(char *str)
{
	int	cnt;

	cnt = -1;
	while (str[++cnt] != '\0')
	{
		if (!(ft_isalnum(str[cnt]) || str[cnt] == '_'))
			return (1);
	}
	return (0);
}
