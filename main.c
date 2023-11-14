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
			echo_builtin();	// execute();
			add_history(str);
			free(str);
			str = NULL;
		}
	}
	return (0);
}
