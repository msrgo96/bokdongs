/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:58:52 by ahn               #+#    #+#             */
/*   Updated: 2023/12/15 00:41:27 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_to_file(t_list *redir_list, t_sh_data *sh_data);
static void	create_hdfile(t_list *env_list, char *path, t_redir *redir);
static void	get_heredoc_input(t_list *env_list, t_redir *redir, int heredoc_fd);

// return : 자식 프로세스의 exit code
// error : proc_list가 null pointer일 시 0 반환
int	heredoc(t_list *proc_list, t_sh_data *sh_data)
{
	t_node	*node;
	t_list	*redir_list;
	int		status;
	pid_t	pid;

	if (!proc_list)
		return (0);
	pid = fork();
	if (pid < 0)
		exit_wrapper(ERR_FORK_FAILED, NULL);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		node = proc_list->head;
		while (node)
		{
			redir_list = ((t_proc *)node->content)->redir_list;
			heredoc_to_file(redir_list, sh_data);
			node = node->next;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	return (status);
}

static void	heredoc_to_file(t_list *redir_list, t_sh_data *sh_data)
{
	t_node	*node;
	t_redir	*redir;
	t_node	*hdfile;

	if (!redir_list)
		return ;
	node = redir_list->head;
	hdfile = sh_data->hdfile_list->head;
	while (node)
	{
		redir = ((t_redir *)node->content);
		if (redir->redir_type == HEREDOC)
		{
			create_hdfile(sh_data->env_list, hdfile->content, redir);
			hdfile = hdfile->next;
		}
		node = node->next;
	}
}

static void	create_hdfile(t_list *env_list, char *path, t_redir *redir)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		exit_wrapper(ERR_OPEN_FAILED, NULL);
	get_heredoc_input(env_list, redir, fd);
	if (close(fd) < 0)
		exit_wrapper(ERR_CLOSE_FAILED, NULL);
}

static void	get_heredoc_input(t_list *env_list, t_redir *redir, int heredoc_fd)
{
	char		*delimiter;
	char		*line;
	char		*expanded_line;
	const char	*heredoc_msg = "heredoc> ";

	delimiter = redir->filename;
	line = readline(heredoc_msg);
	while (line && !ft_str_is_same(line, delimiter))
	{
		expanded_line = expand_string(env_list, line);
		free(line);
		write(heredoc_fd, expanded_line, ft_strlen(expanded_line));
		write(heredoc_fd, "\n", 1);
		free(expanded_line);
		line = readline(heredoc_msg);
	}
	free(line);
}
