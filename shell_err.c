/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:39:08 by moson             #+#    #+#             */
/*   Updated: 2023/12/13 16:24:15 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prt_err_msg(int	exit_code)
{
	(void)exit_code;
	ft_putendl_fd("TEMP MSG", STDERR_FILENO);
	return ;
}

void	exit(int exit_code)
{
	prt_err_msg(exit_code);
	exit(exit_code);
}
