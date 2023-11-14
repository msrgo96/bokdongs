/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jooahn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 21:08:50 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/14 19:36:09 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	if (ac == 1)
	{
		char *input;
		while (1)
		{
			input = readline("$>");
			if (!input)
				continue ;
			rl_replace_line("replaced!\n", 1);
			rl_redisplay();
			add_history(input);
			if (ft_strcmp(input, "exit") == 0)
				exit(EXIT_SUCCESS);
			free(input);
			char *args[] = {"/bin/ls", "-l", NULL};
			// execve(args[0], args, envp);
			return (0);
		}
		clear_history();
		return (0);
	}
}
