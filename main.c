/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:42 by moson             #+#    #+#             */
/*   Updated: 2023/11/07 17:15:28 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


#include "builtins/builtins.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	if (0 && argc && argv && envp)
		return (FT_FALSE);
	while (1)
	{
		str = readline("$> ");
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			free(str);
			str = NULL;
			break ;
		}
		if (str != NULL)
		{
			pwd_builtin((t_sh_data *)0x1, (t_proc *)0x1);	//	TEMP: execute();
			add_history(str);
			free(str);
			str = NULL;
		}
	}
	return (0);
}
