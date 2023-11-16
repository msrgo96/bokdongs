/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:42 by moson             #+#    #+#             */
/*   Updated: 2023/11/16 16:24:22 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			free(str);
			str = NULL;
			break ;
		}
		// jooahn_test
		(void)argc;
		(void)argv;
		(void)envp;
		if (str != NULL)
		{
			// execute();
			add_history(str);
			//tokenizer(str);
			ft_list_iter(tokenizer(str), print_token);
			//free(str);
			str = NULL;
		}
	}
	return (0);
}

void	print_content(void *content)
{
	if (!content)
		printf("content is empty\n");
	else
		printf("content : %s$\n", (char *)content);
}

void	print_token(void *content)
{
	if (!content)
		printf("content is empty\n");
	else
	{
		printf("token's value : %s, ", ((t_token *)content)->value);
		printf("type : %s\n", get_type(((t_token *)content)->type));
	}
}

char	*get_type(int type)
{
	const char	*types[7] = {"in redirection", "out redirection", "add redirection", "heredoc", "pipe", "cmd", 0};

	if (type < 0 || type > 6)
		return (0);
	return ((char *)types[type]);
}
