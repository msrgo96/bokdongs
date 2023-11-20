/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:34:10 by moson             #+#    #+#             */
/*   Updated: 2023/11/20 20:06:05 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# pragma region INCLUDES

# include "libft.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>

# pragma endregion

# pragma region MACROS

# define FT_TRUE 1
# define FT_FALSE 0
# define FT_QUOTES_ERROR_MSG "quotes error!"
# define FT_SYNTAX_ERROR_MSG "syntax error!"

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

//	error code
enum		e_error_code
{
	VALID = 0,
	QUOTES_ERROR = 1,
	SYNTAX_ERROR = 2
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
	char	*absolute_path; // open해서 받아오기
	char	**args;
}			t_proc;

//	(void *)list->content
//	redir_type = e_redir_type
typedef struct s_redir
{
	int		redir_type;
	char	*filename;
}			t_redir;

//	(void *)list->content
typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_sh_data
{
	t_list	*env_list;
}			t_sh_data;

# pragma endregion

t_token		*ft_new_token(void);
void		ft_del_token(void *token);
t_token		*wrap_in_token(void *content);

t_env		*ft_new_env(void);
t_list		*create_env_list(char **envp);

t_list		*tokenizer(char *input);
t_list		*split_include_separator(char *s, const char *sep);
t_list		*split_exclude_separator(char *s);
int			is_in_quotes(char c, int in_quotes[2]);
void		add_sep_in_list(t_list *list, const char *sep, int *i);
void		add_word_in_list(t_list *list, char *s, int i, int *start);

int			check_quotes(char *input);
int			check_syntax(t_list	*token_list);

char		*expand_string(t_list *env_list, char *str);
char		*get_env_value(t_list *env_list, char *key);

t_proc		*ft_new_proc(void);

char		*get_error_msg(int error_code);
void		print_error(int error_code);
void		print_content(void *content);
void		print_env(void *content);
void		print_token(void *content);
char		*get_type(int type);
#endif
