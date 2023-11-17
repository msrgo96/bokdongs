/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:34:10 by moson             #+#    #+#             */
/*   Updated: 2023/11/17 15:42:13 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# pragma region INCLUDES

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# pragma endregion

# pragma region MACROS

# define FT_TRUE 1
# define FT_FALSE 0

# pragma endregion

# pragma region ENUMS

enum		e_quotes_type
{
	SINGLE = 0,
	DOUBLE = 1
};

enum		e_redir_type
{
	I_REDIR = 0,
	O_REDIR = 1,
	A_REDIR = 2,
	HEREDOC = 3
};

//	Extend e_redir_type
enum		e_token_type
{
	PIPE = 4,
	CMD = 5
};

enum		e_fd_type
{
	FDTYPE_STD = 0,
	FDTYPE_PIPE = 1
};

# pragma endregion

# pragma region STRUCTS

//	(void *)list->content
//	type = e_token_type
typedef struct s_token
{
	char	*value;
	int		type;
}			t_token;

//	(void *)list->content
//	default_fdtype = e_fd_type
typedef struct s_proc
{
	int		default_fdtype[2];
	t_list	*redir_list;
	char	*absolute_path;
	char	**args;
	t_list	*envp_list;
}			t_proc;

//	(void *)list->content
//	redir_type = e_redir_type
typedef struct s_redir
{
	int		redir_type;
	char	*filename;
}			t_redir;

//	(void *)list->content
typedef struct s_envp
{
	char	*key;
	char	*value;
}			t_envp;

typedef struct s_sh_data
{
	t_list	*envp_list;
}			t_sh_data;

# pragma endregion

t_token		*ft_new_token(void);
t_token		*wrap_in_token(void *content);

t_list		*tokenizer(char *input);
t_list		*split_include_separator(char *s, const char *sep);
t_list		*split_exclude_separator(char *s);
int			is_in_quotes(char c, int in_quotes[2]);
void		add_sep_in_list(t_list *list, const char *sep, int *i);
void		add_word_in_list(t_list *list, char *s, int i, int *start);

void		print_content(void *content);
void		print_token(void *content);
char		*get_type(int type);
#endif
