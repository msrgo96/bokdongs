/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:14:55 by moson             #+#    #+#             */
/*   Updated: 2023/12/05 13:14:56 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	If malloc error, return (NULL)
//	If there is no PATH in env_list, return ( split = { "dummy_there_is_no_PATH", NULL } )
static char	**get_path_split(t_sh_data *sh_data)
{
	t_node	*path_node;
	t_env	*env;
	char	**split;

	path_node = sh_data->env_list->head;
	while (path_node != NULL)
	{
		env = (t_env *)(path_node->content);
		if (ft_strncmp("PATH", env->key, 5) == 0)
		{
			split = ft_split(env->value, ':');
			return (split);
		}
		path_node = path_node->next;
	}
	split = ft_split("dummy_there_is_no_PATH", ':');
	return (split);
}

static char	*merge_path(char *path, char *file)
{
	char	*res;
	int		cnt;
	int		idx;

	res = (char *)malloc(ft_strlen(path) + 1 + ft_strlen(file) + 1);
	if (res == NULL)
		exit(ERR_MALLOC_FAILED);
	idx = 0;
	while (idx < ft_strlen(path))
	{
		res[idx] = path[idx];
		idx++;
	}
	cnt = 0;
	while ()
}

//	If found, return (ABSOLUTE_PATH)
//	******** WARNING: If NOT found, return (NULL) ********
char	*get_absolute_path(t_sh_data *sh_data, char *cmd)
{
	char	**path_split;
	int		cnt;
	char	*res;

	path_split = get_path_split(sh_data);
	if (path_split == NULL)
		exit(ERR_MALLOC_FAILED);
	cnt = -1;
	res = NULL;
	while (path_split[++cnt] != NULL)
	{
		res = 
	}
}
