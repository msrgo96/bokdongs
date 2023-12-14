/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 00:30:57 by moson             #+#    #+#             */
/*   Updated: 2023/12/14 16:54:38 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prt_err_sub1(int exit_code);

void	prt_err_entrance(int exit_code)
{
	if (exit_code == ERR_UNKNOWN)
		ft_putstr_fd(MSG_UNKNOWN, STDERR_FILENO);
	else if (exit_code == ERR_MALLOC_FAILED)
		ft_putstr_fd(MSG_MALLOC_FAILED, STDERR_FILENO);
	else if (exit_code == ERR_PIPE_FAILED)
		ft_putstr_fd(MSG_PIPE_FAILED, STDERR_FILENO);
	else if (exit_code == ERR_CLOSE_FAILED)
		ft_putstr_fd(MSG_CLOSE_FAILED, STDERR_FILENO);
	else if (exit_code == ERR_FORK_FAILED)
		ft_putstr_fd(MSG_FORK_FAILED, STDERR_FILENO);
	else if (exit_code == ERR_OPEN_FAILED)
		ft_putstr_fd(MSG_OPEN_FAILED, STDERR_FILENO);
	else if (exit_code == ERR_DUP2_FAILED)
		ft_putstr_fd(MSG_DUP2_FAILED, STDERR_FILENO);
	else if (exit_code == ERR_FILE_NOT_EXIST)
		ft_putstr_fd(MSG_FILE_NOT_EXIST, STDERR_FILENO);
	else if (exit_code == ERR_PERM_DENIED)
		ft_putstr_fd(MSG_PERM_DENIED, STDERR_FILENO);
	else if (exit_code == ERR_CMD_NOT_FOUND)
		ft_putstr_fd(MSG_CMD_NOT_FOUND, STDERR_FILENO);
	else if (exit_code == ERR_EXECVE_FAILED)
		ft_putstr_fd(MSG_EXECVE_FAILED, STDERR_FILENO);
	else
		prt_err_sub1(exit_code);
	return ;
}

static void	prt_err_sub1(int exit_code)
{
	if (exit_code == ERR_HEREDOC)
		ft_putstr_fd(MSG_HEREDOC, STDERR_FILENO);
	else if (exit_code == ERR_STAT_FAILED)
		ft_putstr_fd(MSG_STAT_FAILED, STDERR_FILENO);
	else if (exit_code == ERR_EXEC_DIR)
		ft_putstr_fd(MSG_EXEC_DIR, STDERR_FILENO);
	else if (exit_code == ERR_SYNTAX)
		ft_putstr_fd(MSG_SYNTAX, STDERR_FILENO);
	else if (exit_code == ERR_QUOTE)
		ft_putstr_fd(MSG_QUOTE, STDERR_FILENO);
	else
		ft_putstr_fd(MSG_UNDEFINED, STDERR_FILENO);
	return ;
}
