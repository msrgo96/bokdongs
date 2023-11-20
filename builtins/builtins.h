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

# pragma region PROTOTYPES

int	echo_builtin(t_sh_data *sh_data, t_proc *proc);
int	pwd_builtin(t_sh_data *sh_data, t_proc *proc);
int	cd_builtin(t_sh_data *sh_data, t_proc *proc);

# pragma endregion

#endif
