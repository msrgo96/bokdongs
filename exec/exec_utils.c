/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:14:55 by moson             #+#    #+#             */
/*   Updated: 2023/12/05 13:14:56 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_join_three(const char *str1, const char c, const char *str2);
void	prt_err_entrance(int exit_code);

//	Return new **envp for execve()
//	If malloc error, exit (ERR_MALLOC_FAILED)
char	**get_envp_origin(t_list *env_list)
{
	char	**envp;
	t_node	*node;
	t_env	*env;
	int		cnt;

	envp = (char **)malloc(sizeof(char *) * (ft_listsize(env_list) + 1));
	if (envp == NULL)
		exit_wrapper(ERR_MALLOC_FAILED, NULL);
	node = env_list->head;
	cnt = 0;
	while (node != NULL)
	{
		env = (t_env *)(node->content);
		envp[cnt] = str_join_three(env->key, '=', env->value);
		node = node->next;
		cnt++;
	}
	envp[cnt] = NULL;
	return (envp);
}

void	restore_io_fd(t_sh_data *sh_data)
{
	int	res;

	res = dup2(sh_data->fd_std[STDIN_FILENO], STDIN_FILENO);
	if (res == -1)
		exit_wrapper(ERR_DUP2_FAILED, NULL);
	res = dup2(sh_data->fd_std[STDOUT_FILENO], STDOUT_FILENO);
	if (res == -1)
		exit_wrapper(ERR_DUP2_FAILED, NULL);
	res = dup2(sh_data->fd_std[STDERR_FILENO], STDERR_FILENO);
	if (res == -1)
		exit_wrapper(ERR_DUP2_FAILED, NULL);
	return ;
}

int	prt_err(int exit_code, char *target)
{
	if (exit_code != SUCCESS)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		if (target != NULL)
		{
			ft_putstr_fd(target, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		prt_err_entrance(exit_code);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (exit_code);
}

void	exit_wrapper(int exit_code, char *target)
{
	prt_err(exit_code, target);
	exit(exit_code);
}
