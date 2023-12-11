/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:39:08 by moson             #+#    #+#             */
/*   Updated: 2023/12/11 16:39:09 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prt_err_msg(int	exit_code)
{
	(void)exit_code;
	ft_putendl_fd("TEMP MSG", STDERR_FILENO);
	return ;
}

void	exit_with_msg(int exit_code)
{
	prt_err_msg(exit_code);
	exit(exit_code);
}
