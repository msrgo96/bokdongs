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

//	BUILTIN_TEST
int	main(void)
{
	t_sh_data	*sh_data;
	t_proc		*proc;

	//	Init sh_data & proc
	sh_data = (t_sh_data *)malloc(sizeof(t_sh_data) * 1);
	proc = (t_proc *)malloc(sizeof(t_proc) * 1);
	if (sh_data == NULL || proc == NULL)
		return (1);

	//	Set sh_data
	//	...
	//	Set proc
	proc->args = (char **)malloc(sizeof(char *) * 2);
	proc->args[0] = "echo";
	proc->args[1] = NULL;

	echo_builtin(sh_data, proc);
	pwd_builtin(sh_data, proc);
	cd_builtin(sh_data, proc);
	pwd_builtin(sh_data, proc);

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
// 			ft_free((void *)&str);
// 			break ;
// 		}
// 		if (str != NULL)
// 		{
// 			pwd_builtin(NULL, NULL);	//	TEMP: execute();
// 			add_history(str);
// 			ft_free((void *)&str);
// 		}
// 	}
// 	return (0);
// }
