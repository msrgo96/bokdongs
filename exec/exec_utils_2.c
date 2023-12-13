/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:09:59 by moson             #+#    #+#             */
/*   Updated: 2023/12/13 13:10:25 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	If malloc error, return (NULL)
//	If there is no PATH in env_list, return ( split = { NULL } )
char	**get_path_split(t_sh_data *sh_data)
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
	split = (char **)malloc(sizeof(char *) * 1);
	if (split == NULL)
		return (NULL);
	split[0] = NULL;
	return (split);
}

//	Return string format of {str1} + 'c' + {str2} + '\0'
//	If malloc error, exit (ERR_MALLOC_FAILED)
char	*str_join_three(const char *str1, const char c, const char *str2)
{
	char	*res;
	size_t	cnt;
	size_t	idx;

	res = (char *)malloc(ft_strlen(str1) + 1 + ft_strlen(str2) + 1);
	if (res == NULL)
		exit_wrapper(ERR_MALLOC_FAILED, NULL);
	idx = 0;
	while (idx < ft_strlen(str1))
	{
		res[idx] = str1[idx];
		idx++;
	}
	res[idx] = c;
	idx++;
	cnt = 0;
	while (cnt < ft_strlen(str2))
	{
		res[idx] = str2[cnt];
		idx++;
		cnt++;
	}
	res[idx] = '\0';
	return (res);
}

//	If error, exit (ERR_STAT_FAILED)
//	Return the path is directory or not
int	is_a_dir(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		exit_wrapper(ERR_STAT_FAILED, NULL);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (FT_TRUE);
	return (FT_FALSE);
}
