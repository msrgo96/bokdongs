/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_dup2_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:21:52 by moson             #+#    #+#             */
/*   Updated: 2023/12/16 00:52:08 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h> // TO DO : minishell에 있음
#include <errno.h>

int	is_a_dir(char *path);

//	I_REDIR -> O_RDONLY
//	O_REDIR -> O_WRONLY | O_TRUNC | O_CREAT
//	A_REDIR -> O_APPEND | O_CREAT
static int	get_o_flag(int redir_type)
{
	int	res;

	if (redir_type == I_REDIR)
		res = O_RDONLY;
	else if (redir_type == O_REDIR)
		res = O_WRONLY | O_TRUNC | O_CREAT;
	else
		res = O_WRONLY | O_APPEND | O_CREAT;
	return (res);
}

static int	access_redir(char *path, int redir_type)
{
	if (access(path, F_OK) == -1 && errno == 13)
		return (ERR_PERM_DENIED);
	if (redir_type == I_REDIR)
	{
		if (access(path, F_OK) == -1)
			return (ERR_FILE_NOT_EXIST);
		if (access(path, R_OK) == -1)
			return (ERR_PERM_DENIED);
	}
	else
	{
		if (access(path, F_OK) == 0 && is_a_dir(path))
			return (ERR_EXEC_DIR);
		if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
			return (ERR_PERM_DENIED);
	}
	return (SUCCESS);
}

//	If close failed: exit(ERR_CLOSE_FAILED)
//	If dup2 failed: exit(ERR_DUP2_FAILED)
void	dup2_and_close(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		exit_wrapper(ERR_DUP2_FAILED, NULL);
	}
	if (close(fd1) == -1)
	{
		exit_wrapper(ERR_CLOSE_FAILED, NULL);
	}
	return ;
}

void	open_and_dup2_redir_exit(t_redir *redir)
{
	int	access_mode;
	int	fd;
	int	access_res;

	access_res = access_redir(redir->filename, redir->redir_type);
	if (access_res != SUCCESS)
		exit_wrapper(access_res, redir->filename);
	access_mode = get_o_flag(redir->redir_type);
	if (access_mode == O_RDONLY)
	{
		fd = open(redir->filename, access_mode);
		if (fd == -1)
			exit_wrapper(ERR_OPEN_FAILED, NULL);
		dup2_and_close(fd, STDIN_FILENO);
	}
	else
	{
		fd = open(redir->filename, access_mode, 0644);
		if (fd == -1)
			exit_wrapper(ERR_OPEN_FAILED, NULL);
		dup2_and_close(fd, STDOUT_FILENO);
	}
	return ;
}

int	open_and_dup2_redir_return(t_redir *redir)
{
	int	access_mode;
	int	fd;
	int	access_res;

	access_res = access_redir(redir->filename, redir->redir_type);
	if (access_res != SUCCESS)
		return (prt_err(access_res, redir->filename));
	access_mode = get_o_flag(redir->redir_type);
	if (access_mode == O_RDONLY)
	{
		fd = open(redir->filename, access_mode);
		if (fd == -1)
			exit_wrapper(ERR_OPEN_FAILED, NULL);
		dup2_and_close(fd, STDIN_FILENO);
	}
	else
	{
		fd = open(redir->filename, access_mode, 0644);
		if (fd == -1)
			exit_wrapper(ERR_OPEN_FAILED, NULL);
		dup2_and_close(fd, STDOUT_FILENO);
	}
	return (SUCCESS);
}
