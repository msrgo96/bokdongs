/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:54:30 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 15:03:11 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_token_type(t_token *token);
static int	get_token_type(char *str);

t_token	*ft_new_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = 0;
	token->type = -1;
	return (token);
}

t_token	*wrap_in_token(void *content)
{
	t_token	*token;

	token = ft_new_token();
	token->value = content;
	set_token_type(token);
	return (token);
}

static void	set_token_type(t_token *token)
{
	if (!token)
		return ;
	token->type = get_token_type(token->value);
}

static int	get_token_type(char *str)
{
	if (ft_str_is_same(str, "|"))
		return (PIPE);
	if (ft_str_is_same(str, "<<"))
		return (HEREDOC);
	if (ft_str_is_same(str, ">>"))
		return (A_REDIR);
	if (ft_str_is_same(str, "<"))
		return (I_REDIR);
	if (ft_str_is_same(str, ">"))
		return (O_REDIR);
	return (CMD);
}
