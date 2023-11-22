/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str_to_list_util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:53:38 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 16:31:57 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_quote(char c, int in_quote[2])
{
	if (c == '\'')
		in_quote[SINGLE] ^= 1;
	else if (c == '\"')
		in_quote[DOUBLE] ^= 1;
	if (in_quote[SINGLE] || in_quote[DOUBLE])
		return (1);
	return (0);
}

void	add_sep_in_list(t_list *list, const char *sep, int *i)
{
	ft_list_append(list, ft_new_node(ft_strdup(sep)));
	*i += (ft_strlen(sep) - 1);
}

void	add_word_in_list(t_list *list, char *s, int i, int *start)
{
	int	word_len;

	word_len = i - *start;
	if (word_len < 1)
		return ;
	ft_list_append(list, ft_new_node(ft_substr(s, *start, word_len)));
	*start += word_len;
}
