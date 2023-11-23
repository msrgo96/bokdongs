/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:15:32 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/23 21:19:13 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
syntax check & generate_proc_list
return : process list
*/
t_list	*parser(t_list *token_list)
{
	if (!token_list)
		return (0);
	if (check_syntax(token_list) != VALID)
	{
		print_error(SYNTAX_ERROR);
		return (0);
	}
	return (generate_proc_list(token_list));
}
