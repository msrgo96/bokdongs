/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:34:10 by moson             #+#    #+#             */
/*   Updated: 2023/11/10 21:47:44 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <unistd.h>
# include <sys/types.h>

# define FT_ERROR_0 0
# define FT_TRUE 1
# define FT_FALSE 0

enum	e_type
{
	I_REDIR = 0,
	O_REDIR = 1,
	A_REDIR = 2,
	HEREDOC = 3,
	PIPE = 4,
	CMD = 5
};

//	Structs
typedef struct	s_token
{
	char	*value;
	int		type;
}	t_token;

#endif
