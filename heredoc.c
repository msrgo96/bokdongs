/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:58:52 by ahn               #+#    #+#             */
/*   Updated: 2023/12/05 14:40:12 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static void	heredoc_input(t_list *redir_list);
static void	heredoc_to_file(t_redir *redir);
static char	*create_filepath(void);

void	heredoc(t_list *proc_list)
{
	t_node	*node;
	t_list	*redir_list;
	int		status;
	int		pid;

	if (!proc_list)
		return ;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		node = proc_list->head;
		while (node)
		{
			redir_list = ((t_proc *)node->content)->redir_list;
			heredoc_input(redir_list);
			node = node->next;
		}
	}
	else
		waitpid(pid, &status, 0);
}

void	heredoc_clear(void)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*filepath;
	const char		*dirname = "tmp/heredoc";

	dir = opendir(dirname);
	if (dir == NULL)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		filepath = ft_strjoin(dirname, "/", ft_none, ft_none);
		filepath = ft_strjoin(filepath, entry->d_name, free, ft_none);
		unlink(filepath);
		free(filepath);
		entry = readdir(dir);
	}
	closedir(dir);
}

static void	heredoc_input(t_list *redir_list)
{
	t_node	*node;
	t_redir	*redir;

	if (!redir_list)
		return ;
	node = redir_list->head;
	while (node)
	{
		redir = ((t_redir *)node->content);
		if (redir->redir_type == HEREDOC)
			heredoc_to_file(redir);
		node = node->next;
	}
}

static void	heredoc_to_file(t_redir *redir)
{
	int			fd;
	char		*delimiter;
	char		*filepath;
	char		*line;
	const char	*heredoc_msg = "heredoc> ";

	filepath = create_filepath();
	fd = open(filepath, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		exit(EXIT_FAILURE);
	delimiter = redir->filename;
	line = readline(heredoc_msg);
	while (!ft_str_is_same(line, delimiter))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(heredoc_msg);
	}
	free(line);
	free(redir->filename);
	redir->filename = filepath;
	close(fd);
}

static char	*create_filepath(void)
{
	const char	*dir = "tmp/heredoc/";
	static int	cnt;
	char		*filepath;

	filepath = ft_strjoin(dir, ft_itoa(cnt++), ft_none, free);
	while (access(filepath, F_OK) != -1)
	{
		free(filepath);
		filepath = ft_strjoin(dir, ft_itoa(cnt++), ft_none, free);
	}
	return (filepath);
}
