/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_absolute_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 00:57:09 by moson             #+#    #+#             */
/*   Updated: 2023/12/14 16:39:06 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "errno.h"

int		is_a_dir(char *path);
char	**get_path_split(t_sh_data *sh_data);
char	*str_join_three(const char *str1, const char c, const char *str2);

//	TODO: can cmd be NULL?
static int	is_path(char *cmd)
{
	//int	cnt;

	if (cmd == NULL)
		exit_wrapper(ERR_UNKNOWN, "(TODO)cmd is null");
	//cnt = -1;
	return (ft_str_find_chr(cmd, '/') != -1);
	// while (++cnt < ft_strlen(cmd))
	// 	if (cmd[cnt] == '/')
	// 		return (FT_TRUE);
	// return (FT_FALSE);
}

char	*get_absolute_path(t_sh_data *sh_data, char *cmd)
{
	char	*path;

	if (is_path(cmd))
	{
		if (access(cmd, F_OK) != 0 && errno == 13)
			exit_wrapper(ERR_PERM_DENIED, cmd);
		if (is_a_dir(cmd) == FT_TRUE)
			exit_wrapper(ERR_EXEC_DIR, cmd);
		if (access(cmd, F_OK) != 0)
			return (NULL);
		path = ft_strdup(cmd);
		if (path == NULL)
			exit_wrapper(ERR_MALLOC_FAILED, NULL);
		return (path);
	}
	else
	{
		char	**path_split;
		int		cnt;

		path_split = get_path_split(sh_data);
		if (path_split == NULL)
			exit_wrapper(ERR_MALLOC_FAILED, NULL);
		cnt = 0;
		while (path_split[cnt++] != NULL)
		{
			path = str_join_three(path_split[cnt], '/', cmd);



			ft_free((void **)&path);
		}
		ft_split_free(path_split);
		return (path);
	}
}

//	If F_OK, return (ABSOLUTE_PATH)
//	If NOT found, return (NULL)
//	If malloc error, exit (ERR_MALLOC_FAILED)

char	*get_absolute_path_deprecated(t_sh_data *sh_data, char *cmd)
{
	char	**path_split;
	int		cnt;
	char	*path;

	if (access(cmd, F_OK) == 0 && is_a_dir(cmd) == FT_FALSE)
	{
		path = ft_strdup(cmd);
		if (path == NULL)
			exit_wrapper(ERR_MALLOC_FAILED, NULL);
		return (path);
	}
	path_split = get_path_split(sh_data);
	if (path_split == NULL)
		exit_wrapper(ERR_MALLOC_FAILED, NULL);
	cnt = -1;
	while (path_split[++cnt] != NULL)
	{
		path = str_join_three(path_split[cnt], '/', cmd);
		if (path == NULL)
			exit_wrapper(ERR_MALLOC_FAILED, NULL);
		if (access(path, F_OK) == 0 && is_a_dir(path) == FT_FALSE)
			break ;
		ft_free((void **)&path);
	}
	ft_split_free(path_split);
	return (path);
}
