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

//	Return string format of {str1} + 'c' + {str2} + '\0'
//	If malloc error, exit (ERR_MALLOC_FAILED)
char	*str_join_three(const char *str1, const char c, const char *str2)
{
	char	*res;
	size_t	cnt;
	size_t	idx;

	res = (char *)malloc(ft_strlen(str1) + 1 + ft_strlen(str2) + 1);
	if (res == NULL)
		exit(ERR_MALLOC_FAILED);
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
static int	is_a_dir(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		exit(ERR_STAT_FAILED);
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
		return (FT_TRUE);
	return (FT_FALSE);
}

//	If F_OK, return (ABSOLUTE_PATH)
//	If NOT found, return (NULL)
//	If malloc error, exit (ERR_MALLOC_FAILED)
char	*get_absolute_path(t_sh_data *sh_data, char *cmd)
{
	char	**path_split;
	int		cnt;
	char	*path;

	if (access(cmd, F_OK) == 0 && is_a_dir(cmd) == FT_FALSE)
	{
		path = ft_strdup(cmd);
		if (path == NULL)
			exit(ERR_MALLOC_FAILED);
		return (path);
	}
	path_split = get_path_split(sh_data);
	if (path_split == NULL)
		exit(ERR_MALLOC_FAILED);	
	cnt = -1;
	while (path_split[++cnt] != NULL)
	{
		path = str_join_three(path_split[cnt], '/', cmd);
		if (path == NULL)
			exit(ERR_MALLOC_FAILED);
		if (access(path, F_OK) == 0 && is_a_dir(path) == FT_FALSE)
			break ;
		ft_free((void **)&path);
	}
	ft_split_free(path_split);
	return (path);
}
