/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:42 by moson             #+#    #+#             */
/*   Updated: 2023/12/14 23:37:15 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

void	print_proc(void *content);
void	print_redir(void *content);

int	g_exit_code = 0;

void	leaks_test(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_list		*proc_list;
	t_sh_data	*sh_data;

	atexit(leaks_test);
	(void)argc;
	(void)argv;
	sh_data = ft_new_sh_data(envp);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, display_new_prompt);
		str = readline("$> ");
		if (!str)
		{
			printf("exit\n");
			ft_free((void **)&str);
			break ;
		}
		add_history(str);
		proc_list = parser(str, sh_data->env_list);
		if (!proc_list)
		{
			ft_free((void **)&str);
			continue;
		}
		set_proc_sh_data(sh_data, proc_list);
		g_exit_code = executor(sh_data, proc_list);
		ft_list_iter(proc_list, print_proc);
		print_if_signaled(sh_data);
		clear_after_input(str, sh_data, proc_list);
	}
	clear_shell(sh_data);
	return (0);
}

void	print_proc(void *content)
{
	t_proc	*proc;
	char	**args;
	int		i = 0;

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
		if (!args)
			printf("(null)");
		else
		{
			while (args[i])
			{
				printf("[%s], ", args[i]);
				i++;
			}
		}
		printf("\n");
		printf("redir_list : ");
		if (!(proc->redir_list))
			printf("(null)");
		if (ft_list_is_empty(proc->redir_list))
			printf("empty");
		ft_list_iter(proc->redir_list, print_redir);
		printf("\n");
		printf("--- ------- --- \n");
	}
}

void	print_redir(void *content)
{
	t_redir	*redir;

	if (!content)
	{
		printf("(null)");
		return ;
	}
	redir = ((t_redir *)content);
	printf("(type : %d, ", redir->redir_type);
	printf("file name : %s), ", redir->filename);
}

// void	print_content(void *content)
// {
// 	if (!content)
// 		printf("content is empty\n");
// 	else
// 		printf("content : %s$\n", (char *)content);
// }

// void	print_env(void *content)
// {
// 	if (!content)
// 		printf("content is empty\n");
// 	else
// 	{
// 		printf("env's key : %s, ", ((t_env *)content)->key);
// 		printf("value : %s\n", ((t_env *)content)->value);
// 	}
// }
