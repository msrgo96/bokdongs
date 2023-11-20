/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 04:10:46 by moson             #+#    #+#             */
/*   Updated: 2023/11/21 04:10:47 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"

//	Return arguments length
//	If args is NULL, return 0
int	get_args_len(char **args)
{
	int	len;

	if (args == NULL)
		return (0);
	len = 0;
	while (args[len] != NULL)
		len++;
	return (len);
}
