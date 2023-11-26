/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 05:04:32 by moson             #+#    #+#             */
/*   Updated: 2023/11/15 05:04:33 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft.h"
# include <errno.h>

# define NOT_A_BUILTIN -1
# define SUCCESS 0
# define UNKNOWN_MSG "unknown error"

# define ENV_NULPTR 1
# define ENV_NULPTR_MSG "null pointer exception"

# define UNSET_NOTEXIST 0
# define UNSET_NULPTR 1
# define UNSET_NULPTR_MSG "null pointer exception"
# define UNSET_UNKNOWN 2
# define UNSET_UNKNOWN_MSG "unknown error"

# define EXPORT_NULPTR 1
# define EXPORT_NULPTR_MSG "null pointer exception"
# define EXPORT_UNKNOWN 2
# define EXPORT_UNKNOWN_MSG "unknown error"
# define EXPORT_FORMAT 3
# define EXPORT_FORMAT_MSG "format error"

# define EXIT_NAN 255
# define EXIT_NAN_MSG "argument is not a number"

int	exec_builtin(t_sh_data *sh_data, t_proc *proc);

int	echo_builtin(t_sh_data *sh_data, t_proc *proc);
int	pwd_builtin(t_sh_data *sh_data, t_proc *proc);
int	cd_builtin(t_sh_data *sh_data, t_proc *proc);
int	env_builtin(t_sh_data *sh_data, t_proc *proc);
int	unset_builtin(t_sh_data *sh_data, t_proc *proc);
int	export_builtin(t_sh_data *sh_data, t_proc *proc);
int	exit_builtin(t_sh_data *sh_data, t_proc *proc);

#endif
