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
		argc++;
		argv++;
		envp++;
		//ft_list_iter(tokenizer(str), print_content);
		if (str != NULL)
		{
			// execute();
			add_history(str);
			tokenizer(str);
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
		printf("content : %s\n", (char *)content);
}
