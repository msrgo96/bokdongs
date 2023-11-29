/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahn <ahn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:58:52 by ahn               #+#    #+#             */
/*   Updated: 2023/11/29 21:39:32 by ahn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	heredoc_input(t_list *redir_list);
char	*create_filename(void);
void	heredoc_to_file(t_redir *redir);

	void heredoc(t_list *proc_list)
{
	t_node	*node;
	t_list	*redir_list;

	node = proc_list->head;
	while (node)
	{
		redir_list = ((t_proc *)node->content)->redir_list;
		heredoc_input(redir_list);
		node = node->next;
	}
}

void	heredoc_input(t_list *redir_list)
{
	int		status;
	int		pid;
	t_node	*node;
	t_redir	*redir;

	node = redir_list->head;
	while (node)
	{
		redir = ((t_redir *)node->content);
		if (redir->redir_type == HEREDOC)
		{
			pid = fork();
			if (pid < 0)
				exit(EXIT_FAILURE);
			if (pid == 0)
				heredoc_to_file(redir);
			else
				waitpid(pid, &status, 0);
		}
		node = node->next;
	}
}

void	heredoc_to_file(t_redir *redir)
{
	int		fd;
	char	*delimiter;
	char	*filename;
	char	*line;

	filename = create_filename();
	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		exit(EXIT_FAILURE);
	delimiter = redir->filename;
	line = readline("heredoc> ");
	while (!ft_str_is_same(line, delimiter))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	free(redir->filename);
	redir->filename = filename;
	close(fd);
}

char	*create_filename(void)
{
	const char *filename_form = ".tmp_";
	static int cnt;
	char *filename;

	filename = ft_strjoin(filename_form, ft_itoa(cnt++), ft_none, free);
	while (access(filename, F_OK) != -1)
	{
		free(filename);
		filename = ft_strjoin(filename_form, ft_itoa(cnt++), ft_none, free);
	}
	return (filename);
}