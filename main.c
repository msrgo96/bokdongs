/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:42 by moson             #+#    #+#             */
/*   Updated: 2023/12/16 00:35:56 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_list		*proc_list;
	t_sh_data	*sh_data;

	if (argc != 1)
		return (0);
	init_shell(argv, envp, &sh_data);
	while (1)
	{
		signal(SIGINT, display_new_prompt);
		str = readline("$> ");
		if (!str)
			break ;
		if (*str)
			add_history(str);
		proc_list = parser(str, sh_data->env_list);
		if (proc_list)
			g_exit_code = executor(sh_data, proc_list);
		print_newline_if_signaled(sh_data);
		clear_after_input(str, sh_data, proc_list);
	}
	printf("exit\n");
	clear_shell(sh_data);
	return (0);
}
