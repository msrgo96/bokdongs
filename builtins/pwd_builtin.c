/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:04:43 by moson             #+#    #+#             */
/*   Updated: 2023/11/16 23:04:44 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

//	Return errno_getcwd
/*	TEMP..
// if (errno_getcwd == EACCES)
	// 	str = 
	// else if (errno_getcwd == EFAULT)
	// 	str = 
	// else if (errno_getcwd == EINVAL)
	// 	str = 
	// else if (errno_getcwd == ELOOP)
	// 	str = 
	// else if (errno_getcwd == ENAMETOOLONG)
	// 	str = 
	// else if (errno_getcwd == ENOENT)
	// 	str = 
	// else if (errno_getcwd == ERANGE)
	// 	str = 
	// else
	// 	str = 
*/
static int	print_pwd_err(const int errno_getcwd)
{
	char	*str;

	str = strerror(errno_getcwd);
	ft_putstr_fd("pwd: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (errno_getcwd);
}

//	Return exit code of getcwd()
int	pwd_builtin(t_sh_data *sh_data, t_proc *proc)
{
	char	*buf;
	int		errno_getcwd;

	sh_data++;
	proc++;
	errno_getcwd = 0;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
		errno_getcwd = errno;
	if (errno_getcwd == 0)
		ft_printf("%s\n", buf);
	else
		errno_getcwd = print_pwd_err(errno_getcwd);
	ft_free((void *)&buf);
	return (errno_getcwd);
}
