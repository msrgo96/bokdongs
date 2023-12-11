/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:15:32 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/11 22:48:34 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

/*
syntax check & generate_proc_list
return : process list
*/
t_list	*parser(t_list *token_list)
{
	if (!token_list)
		return (0);
	if (check_syntax(token_list) != SUCCESS)
	{
		g_exit_code = ERR_SYNTAX;
		prt_err_msg(ERR_SYNTAX);
		return (0);
	}
	return (generate_proc_list(token_list));
}
