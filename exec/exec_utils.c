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

void	dup2_and_close(int fd1, int fd2);

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
static char	*str_join_three(const char *str1, const char c, const char *str2)
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

//	If F_OK, return (ABSOLUTE_PATH)
//	If NOT found, return (NULL)
//	If malloc error, exit (ERR_MALLOC_FAILED)
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
		res = str_join_three(path_split[cnt], '/', cmd);
		if (access(res, F_OK) == 0)
			break ;
		ft_free((void **)&res);
	}
	ft_split_free(path_split);
	return (res);
}

//	Return new **envp for execve()
//	If malloc error, exit (ERR_MALLOC_FAILED)
char	**get_envp_origin(t_list *env_list)
{
	char	**envp;
	t_node	*node;
	t_env	*env;
	int		cnt;

	envp = (char **)malloc(sizeof(char *) * (ft_listsize(env_list) + 1));
	if (envp == NULL)
		exit (ERR_MALLOC_FAILED);
	node = env_list->head;
	cnt = 0;
	while (node != NULL)
	{
		env = (t_env *)(node->content);
		envp[cnt] = str_join_three(env->key, '=', env->value);
		node = node->next;
		cnt++;
	}
	envp[cnt] = NULL;
	return (envp);
}

void	restore_io_fd(t_sh_data *sh_data)
{
	int	res;

	res = dup2(sh_data->fd_std[STDIN_FILENO], STDIN_FILENO);
	if (res == -1)
		exit(ERR_DUP2_FAILED);
	res = dup2(sh_data->fd_std[STDOUT_FILENO], STDOUT_FILENO);
	if (res == -1)
		exit(ERR_DUP2_FAILED);
	res = dup2(sh_data->fd_std[STDERR_FILENO], STDERR_FILENO);
	if (res == -1)
		exit(ERR_DUP2_FAILED);
	return ;
}
