/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:06:52 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/22 22:02:45 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(int in_quote[2], char **expanded_str, int *i);
static int	quote_need_remove(int in_quote[2], char c);
static char	*expand_env(t_list *env_list, char *str, int *i);

/*
remove quote & expand env
return : char *
*/
char	*expand_string(t_list *env_list, char *str)
{
	int		in_quote[2];
	char	*expanded_str;
	int		i;

	if (!env_list || !str)
		return (0);
	init_data(in_quote, &expanded_str, &i);
	while (str[++i])
	{
		if (quote_need_remove(in_quote, str[i]))
			continue ;
		if (*str == '$' && *(str + 1) && !in_quote[SINGLE])
			expanded_str = ft_strjoin(expanded_str, \
			expand_env(env_list, str, &i), free, ft_none);
		else
			expanded_str = ft_str_append(expanded_str, str[i], free);
	}
	return (expanded_str);
}

void	expand_string_iter(t_list *token_list, t_list *env_list, \
char *(*expand_string)(t_list *, char *), void (*del)(void *))
{
	t_node	*node;
	t_token	*token;
	char	*temp;

	if (!token_list)
		return ;
	node = token_list->head;
	while (node)
	{
		token = (t_token *)(node->content);
		temp = token->value;
		token->value = expand_string(env_list, token->value);
		del(temp);
		node = node->next;
	}
}

static void	init_data(int in_quote[2], char **expanded_str, int *i)
{
	in_quote[SINGLE] = 0;
	in_quote[DOUBLE] = 0;
	*i = -1;
	*expanded_str = ft_new_str(0);
}

static int	quote_need_remove(int in_quote[2], char c)
{
	if (c == '\'' && !in_quote[DOUBLE])
	{
		in_quote[SINGLE] ^= 1;
		return (1);
	}
	if (c == '\"' && !in_quote[SINGLE])
	{
		in_quote[DOUBLE] ^= 1;
		return (1);
	}
	return (0);
}

static char	*expand_env(t_list *env_list, char *str, int *i)
{
	char	*env_value;
	char	*key;
	int		start;

	if (!env_list || !str || !i || str[*i] != '$')
		return (0);
	start = ++(*i);
	if (ft_isalnum(str[start]))
		while (str[*i] && ft_isalnum(str[*i]))
			(*i)++;
	else
		(*i)++;
	key = ft_substr(str, start, *i - start);
	env_value = get_env_value(env_list, key);
	free(key);
	(*i)--;
	return (env_value);
}
