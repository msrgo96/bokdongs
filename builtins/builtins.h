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

# pragma region ERRCODE

# define EXIT_SUCCESS 0

# define ENV_NULPTR 1

//	NOTEXIST = SUCCESS
# define UNSET_NOTEXIST 0
# define UNSET_NULPTR 1
# define UNSET_UNKNOWN 2

# pragma endregion

# pragma region PROTOTYPES

int	echo_builtin(t_sh_data *sh_data, t_proc *proc);
int	pwd_builtin(t_sh_data *sh_data, t_proc *proc);
int	cd_builtin(t_sh_data *sh_data, t_proc *proc);
int	env_builtin(t_sh_data *sh_data, t_proc *proc);
int	unset_builtin(t_sh_data *sh_data, t_proc *proc);

# pragma endregion

#endif
