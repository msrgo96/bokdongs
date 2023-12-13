/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_dup2_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:21:52 by moson             #+#    #+#             */
/*   Updated: 2023/12/04 17:21:54 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

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
		res = O_APPEND | O_CREAT;
	return (res);
}

//	If file not exist: exit(ERR_FILE_NOT_EXIST)
//	If permission denied: exit(ERR_PERM_DENIED)
static void	access_redir(char *path, int redir_type)
{
	int	access_mode;

	if (redir_type == I_REDIR)
		if (access(path, F_OK) == -1)
			exit_wrapper(ERR_FILE_NOT_EXIST, path);
	if (redir_type == I_REDIR)
		access_mode = R_OK;
	else
		access_mode = W_OK;
	if (access(path, F_OK) != -1 && access(path, access_mode) == -1)
		exit_wrapper(ERR_PERM_DENIED, path);
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

//	open as redir, dup2 each STD I/O, and finally close fd when open
//	If error, exit(ERR_OPEN_FAILED, ERR_DUP2_FAILED, ERR_FILE_NOT_EXIST, ERR_PERM_DENIED)
void	open_and_dup2_redir(t_redir *redir)
{
	int	redir_type;
	int	fd;

	redir_type = get_o_flag(redir->redir_type);
	access_redir(redir->filename, redir_type);
	if (redir_type == O_RDONLY)
	{
		fd = open(redir->filename, redir_type);
		if (fd == -1)
			exit_wrapper(ERR_OPEN_FAILED, NULL);
		dup2_and_close(fd, STDIN_FILENO);
	}
	else
	{
		fd = open(redir->filename, redir_type, 0644);
		if (fd == -1)
			exit_wrapper(ERR_OPEN_FAILED, NULL);
		dup2_and_close(fd, STDOUT_FILENO);
	}
	return ;
}
