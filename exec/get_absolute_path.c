/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_absolute_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 00:57:09 by moson             #+#    #+#             */
/*   Updated: 2023/12/14 00:57:13 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "errno.h"

int		is_a_dir(char *path);
char	**get_path_split(t_sh_data *sh_data);
char	*str_join_three(const char *str1, const char c, const char *str2);

static int	is_path(char *cmd)
{
	int	cnt;
	int	len;

	cnt = -1;
	len = ft_strlen(cmd);
	while (++cnt < len)
		if (cmd[cnt] == '/')
			return (FT_TRUE);
	return (FT_FALSE);
}

//	return ABS_PATH or exit
//	exit with (ERR_FILE_NOT_EXIST, ERR_PERM_DENIED, ERR_STAT_FAILED, ERR_EXEC_DIR, ERR_MALLOC_FAILED)
static char	*get_absolute_path_binary(char *path)
{
	char	*res;

	if (access(path, F_OK) != 0 && errno == 13)
		exit_wrapper(ERR_PERM_DENIED, path);
	if (is_a_dir(path) == FT_TRUE)
		exit_wrapper(ERR_EXEC_DIR, path);
	if (access(path, F_OK) != 0)
		exit_wrapper(ERR_FILE_NOT_EXIST, path);
	if (access(path, X_OK) != 0)
		exit_wrapper(ERR_PERM_DENIED, path);
	res = ft_strdup(path);
	if (res == NULL)
		exit_wrapper(ERR_MALLOC_FAILED, NULL);
	return (res);
}

//	return ABS_PATH or exit
//	exit with (ERR_MALLOC_FAILED, ERR_STAT_FAILED, ERR_CMD_NOT_FOUND)
static char	*get_absolute_path_cmd(t_sh_data *sh_data, char *cmd)
{
	char	*path;
	char	**path_split;
	int		cnt;

	path_split = get_path_split(sh_data);
	if (path_split == NULL)
		exit_wrapper(ERR_MALLOC_FAILED, NULL);
	cnt = -1;
	while (path_split[++cnt] != NULL)
	{
		path = str_join_three(path_split[cnt], '/', cmd);
		if (access(path, X_OK) == 0 && !is_a_dir(path))
		{
			ft_split_free(path_split);
			return (path);
		}
		ft_free((void **)&path);
	}
	ft_split_free(path_split);
	exit_wrapper(ERR_CMD_NOT_FOUND, cmd);
	return (NULL);
}

//	return ABS_PATH or exit
//	exit with (ERR_FILE_NOT_EXIST, ERR_CMD_NOT_FOUND, ERR_PERM_DENIED, ERR_STAT_FAILED, ERR_EXEC_DIR, ERR_MALLOC_FAILED)
char	*get_absolute_path(t_sh_data *sh_data, char *cmd)
{
	if (is_path(cmd))
		return (get_absolute_path_binary(cmd));
	else
		return (get_absolute_path_cmd(sh_data, cmd));
}
