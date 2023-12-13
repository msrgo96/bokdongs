/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:42 by moson             #+#    #+#             */
/*   Updated: 2023/12/13 16:21:08 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins/builtins.h"

#pragma region PROTOTYPES

int		set_proc_sh_data(t_sh_data *sh_data, t_list *proc_list);
void	clear_proc_sh_data(t_sh_data *sh_data);
int		executor(t_sh_data *sh_data, t_list *proc_list);

#pragma endregion

int	g_exit_code = 0;

void	leaks_test(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_list		*token_list;
	t_list		*proc_list;
	t_sh_data	*sh_data;

	//atexit(leaks_test);
	(void)argc;
	(void)argv;

	//	INIT t_sh_data
	sh_data = (t_sh_data *)malloc(sizeof(t_sh_data) * 1);
	if (sh_data == NULL)
		return (1);
	sh_data->env_list = convert_envp_to_env_list(envp);
	sh_data->fd_std[STDIN_FILENO] = dup(STDIN_FILENO);
	sh_data->fd_std[STDOUT_FILENO] = dup(STDOUT_FILENO);
	sh_data->fd_std[STDERR_FILENO] = dup(STDERR_FILENO);

	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, display_new_prompt);
		str = readline("$> ");
		if (!str)
		{
			ft_printf("exit\n");
			break ;
		}
		if (str != NULL)
		{
			if (str[0] == '\0')
			{
				ft_free((void *)&str);
				g_exit_code = 0;
				continue ;
			}
			add_history(str);
			if (check_quote(str) != SUCCESS)
			{
				g_exit_code = ERR_QUOTE;
				prt_err(ERR_QUOTE, NULL);
				ft_free((void *)&str);
				continue ;
			}
			token_list = tokenizer(str);
			if (!token_list)
				continue;
			expand_string_iter(token_list, sh_data->env_list, expand_string, free);
			proc_list = parser(token_list);
			if (proc_list)
			{
				set_proc_sh_data(sh_data, proc_list);
				g_exit_code = executor(sh_data, proc_list);

				// if (g_exit_code == SIGNAL_OFFSET + SIGINT)
				// 	write(1, "\n", 1); // 자식프로세스가 인터럽트로 꺼졌을 시 프롬프트 깨끗하게 해주는 부분

				for (int i = 0; i < sh_data->proc_size; i++)
					if (sh_data->exit_status[i] == SIGNAL_OFFSET + SIGINT)
					{
						write(1, "\n", 1); // 자식프로세스가 인터럽트로 꺼졌을 시 프롬프트 깨끗하게 해주는 부분
						break ;
					}

				clear_proc_sh_data(sh_data);
				ft_list_clear(proc_list, ft_del_proc);
			}
			ft_list_clear(token_list, ft_del_token);
		}
	}
	ft_list_clear(sh_data->env_list, ft_del_env);
	ft_free((void **)&sh_data);
	return (0);
}

/* TO DO
'<< a' 입력 후 echo $? -> 11(EXECVE FAILED) 나옴. "" 입력시에도 마찬가지
sanitizer로 하면 위 상황에서 세그폴트 나옴
*/

// void	print_proc(void *content)
// {
// 	t_proc	*proc;
// 	char	**args;

// 	proc = ((t_proc *)content);
// 	if (!content)
// 		printf("content is empty\n");
// 	else
// 	{
// 		printf("\n--- process --- \n");
// 		printf("read_fd : %d\n", proc->default_fdtype[READ_FD]);
// 		printf("write_fd : %d\n", proc->default_fdtype[WRITE_FD]);
// 		printf("args : ");
// 		args = proc->args;
// 		while (*args)
// 		{
// 			printf("[%s], ", *args);
// 			args++;
// 		}
// 		printf("\n");
// 		printf("redir_list : ");
// 		ft_list_iter(proc->redir_list, print_redir);
// 		printf("\n");
// 		printf("--- ------- --- \n");
// 	}
// }

// void	print_redir(void *content)
// {
// 	t_redir	*redir;

// 	redir = ((t_redir *)content);
// 	if (!content)
// 		printf("content is empty\n");
// 	else
// 	{
// 		printf("(type : %d, ", redir->redir_type);
// 		printf("file name : %s), ", redir->filename);
// 	}
// }

// void	print_content(void *content)
// {
// 	if (!content)
// 		printf("content is empty\n");
// 	else
// 		printf("content : %s$\n", (char *)content);
// }

// void	print_token(void *content)
// {
// 	if (!content)
// 		printf("content is empty\n");
// 	else
// 	{
// 		printf("token's value : %s, ", ((t_token *)content)->value);
// 		printf("type : %s\n", get_type(((t_token *)content)->type));
// 	}
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

// char	*get_type(int type)
// {
// 	const char *types[7] = {"in redirection", "out redirection",
// 		"add redirection", "heredoc", "pipe", "cmd", 0};
// 	if (type < 0 || type > 6)
// 		return (0);
// 	return ((char *)types[type]);
// }
