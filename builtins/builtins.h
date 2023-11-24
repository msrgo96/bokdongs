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

# pragma region ERROR

# define EXIT_SUCCESS 0
# define UNKNOWN_MSG "unknown error"

# define ENV_NULPTR 1
# define ENV_NULPTR_MSG "null pointer exception"

//	NOTEXIST = SUCCESS
# define UNSET_NOTEXIST 0
# define UNSET_NULPTR 1
# define UNSET_NULPTR_MSG "null pointer exception"
# define UNSET_UNKNOWN 2
# define UNSET_UNKNOWN_MSG "unknown error"

# define EXPORT_NULPTR 1
# define EXPORT_NULPTR_MSG "null pointer exception"
# define EXPORT_UNKNOWN 2
# define EXPORT_UNKNOWN_MSG "unknown error"


# pragma endregion

# pragma region PROTOTYPES

int	echo_builtin(t_sh_data *sh_data, t_proc *proc);
int	pwd_builtin(t_sh_data *sh_data, t_proc *proc);
int	cd_builtin(t_sh_data *sh_data, t_proc *proc);
int	env_builtin(t_sh_data *sh_data, t_proc *proc);
int	unset_builtin(t_sh_data *sh_data, t_proc *proc);
int	export_builtin(t_sh_data *sh_data, t_proc *proc);

# pragma endregion

#endif
