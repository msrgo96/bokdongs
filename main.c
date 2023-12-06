/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:42 by moson             #+#    #+#             */
/*   Updated: 2023/12/07 00:25:28 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 1;

void	leaks_test(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_list	*env_list;
	t_list	*token_list;
	t_list	*proc_list;

	//atexit(leaks_test);
	(void)argc;
	(void)argv;
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		str = readline("$> ");
		if (!str)
			return (0);
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			free(str);
			str = NULL;
			break ;
		}
		if (str != NULL)
		{
			add_history(str);
			if (check_quote(str) != VALID)
			{
				print_error(QUOTE_ERROR);
				free(str);
				continue ;
			}
			env_list = convert_envp_to_env_list(envp);
			token_list = tokenizer(str);
			expand_string_iter(token_list, env_list, expand_string, free);
			proc_list = parser(token_list);
			t_sh_data sh_data;
			sh_data.hdfile_list = ft_new_list();
			sh_data.env_list = env_list;
			if (set_hdfile_list(proc_list, sh_data.hdfile_list) > 0)
			{
				heredoc(proc_list, &sh_data);
				replace_filename(proc_list, sh_data.hdfile_list);
			}
			ft_list_iter(proc_list, print_proc);
			//	FUNC
			heredoc_clear(sh_data.hdfile_list);
			ft_list_clear(token_list, ft_del_token);
			ft_list_clear(env_list, ft_del_env);
			ft_list_clear(proc_list, ft_del_proc);
		}
	}
	return (0);
}

void	print_proc(void *content)
{
	t_proc	*proc;
	char	**args;

	proc = ((t_proc *)content);
	if (!content)
		printf("content is empty\n");
	else
	{
		printf("\n--- process --- \n");
		printf("read_fd : %d\n", proc->default_fdtype[READ_FD]);
		printf("write_fd : %d\n", proc->default_fdtype[WRITE_FD]);
		printf("args : ");
		args = proc->args;
		while (*args)
		{
			printf("[%s], ", *args);
			args++;
		}
		printf("\n");
		printf("redir_list : ");
		ft_list_iter(proc->redir_list, print_redir);
		printf("\n");
		printf("--- ------- --- \n");
	}
}

void	print_redir(void *content)
{
	t_redir	*redir;

	redir = ((t_redir *)content);
	if (!content)
		printf("content is empty\n");
	else
	{
		printf("(type : %d, ", redir->redir_type);
		printf("file name : %s), ", redir->filename);
	}
}

void	print_error(int error_code)
{
	printf("%s\n", get_error_msg(error_code));
	// exit(EXIT_FAILURE);
}

char	*get_error_msg(int error_code)
{
	if (error_code == QUOTE_ERROR)
		return (FT_QUOTE_ERROR_MSG);
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
	const char *types[7] = {"in redirection", "out redirection",
		"add redirection", "heredoc", "pipe", "cmd", 0};
	if (type < 0 || type > 6)
		return (0);
	return ((char *)types[type]);
}
