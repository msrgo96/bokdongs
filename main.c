/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:42 by moson             #+#    #+#             */
/*   Updated: 2023/11/20 20:56:29 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void leaks_test(void) {
    system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	//atexit(leaks_test);
	while (1)
	{
		// t_list *env_list = create_env_list(envp);
		// ft_list_iter(env_list, print_env);
		// return (0);
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
			// char *value = get_env_value(create_env_list(envp), str);
			// printf("%s\n", value);
			char *expanded_str = expand_string(create_env_list(envp), str);
			printf("%s\n", expanded_str);
			//tokenizer(str);
			// int error_code = check_quotes(str);
			// if (error_code != VALID)
			// {
			// 	print_error(error_code);
			// 	free(str);
			// 	continue ;
			// }
			/* syntax checker test
			t_list *token_list = tokenizer(str);
			if (check_syntax(token_list) != VALID)
				print_error(SYNTAX_ERROR);
			else
				printf("syntax ok\n");
			*/
			/* token_list clear test
			ft_list_clear(token_list, ft_del_token);
			*/
			//ft_list_iter(tokenizer(str), print_token);
			//free(str);
			str = NULL;
		}
	}
	return (0);
}

void	print_error(int error_code)
{
	printf("%s\n", get_error_msg(error_code));
	//exit(EXIT_FAILURE);
}

char	*get_error_msg(int error_code)
{
	if (error_code == QUOTES_ERROR)
		return (FT_QUOTES_ERROR_MSG);
	if (error_code == SYNTAX_ERROR)
		return (FT_SYNTAX_ERROR_MSG);
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

void	print_env(void *content)
{
	if (!content)
		printf("content is empty\n");
	else
	{
		printf("env's key : %s, ", ((t_env *)content)->key);
		printf("value : %s\n", ((t_env *)content)->value);
	}
}

char	*get_type(int type)
{
	const char	*types[7] = {"in redirection", "out redirection", "add redirection", "heredoc", "pipe", "cmd", 0};

	if (type < 0 || type > 6)
		return (0);
	return ((char *)types[type]);
}
