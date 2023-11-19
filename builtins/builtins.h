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

# pragma region EXIT_CODES

# define ECHO_SUCCESS 0

# define PWD_SUCCESS 0
# define PWD_MALLOC_FAILED 1
# define PWD_ARGS_ERROR 2

# define CD_NO_EXIST_DIR 1
# define CD_NOT_A_DIR 1
# define CD_NO_AUTH 1


# pragma endregion

# pragma region PROTOTYPES

int	echo_builtin(t_sh_data *sh_data, t_proc *proc);
int	pwd_builtin(t_sh_data *sh_data, t_proc *proc);

# pragma endregion

#endif
