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

int	main(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	ft_printf("%s\n", str);

	chdir(ft_strjoin(str, "/.a"));
	// TEMP: Check getcwd() or chdir() return value for SUCCESS

	str = getcwd(NULL, 0);
	ft_printf("%s\n", str);

	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*str;

// 	if (0 && argc && argv && envp)
// 		return (FT_FALSE);
// 	while (1)
// 	{
// 		str = readline("$> ");
// 		if (ft_strncmp(str, "exit", 5) == 0)
// 		{
// 			free(str);
// 			str = NULL;
// 			break ;
// 		}
// 		if (str != NULL)
// 		{
// 			// execute();
// 			add_history(str);
// 			free(str);
// 			str = NULL;
// 		}
// 	}
// 	return (0);
// }
