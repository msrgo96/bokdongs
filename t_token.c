/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:54:30 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/12 22:28:34 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit_with_msg(ERR_MALLOC_FAILED);
	token->value = 0;
	token->type = -1;
	return (token);
}

void	ft_del_token(void *token)
{
	if (!token)
		return ;
	free(((t_token *)token)->value);
	((t_token *)token)->value = 0;
	free(token);
	token = 0;
}

t_token	*wrap_in_token(void *content)
{
	t_token	*token;

	token = ft_new_token();
	token->value = content;
	set_token_type(token);
	return (token);
}

void	set_token_type(t_token *token)
{
	if (!token)
		return ;
	token->type = get_token_type(token->value);
}

int	get_token_type(char *str)
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
