/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:15:32 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/12 23:48:14 by jooahn           ###   ########.fr       */
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
	{
		g_exit_code = 0;
		return (0);
	}
	if (check_syntax(token_list) != SUCCESS)
	{
		g_exit_code = ERR_SYNTAX;
		prt_err(ERR_SYNTAX, NULL);
		return (0);
	}
	return (generate_proc_list(token_list));
}
