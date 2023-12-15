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

extern int	g_exit_code;

static int	quote_need_remove(int in_quote[2], char c);
static int	is_need_expand(char *str, int *in_quote);
static char	*expand_env(t_list *env_list, char *str, int *i);

/*
입력 문자열에서 짝 맞는 바깥쪽 따옴표 제거 및 env_list 기준으로 환경변수 확장
return : char *
error : return NULL pointer
*/
char	*expand_string(t_list *env_list, char *str)
{
	int		in_quote[2];
	char	*expanded_str;
	int		i;

	if (!str)
		return (0);
	in_quote[SINGLE] = 0;
	in_quote[DOUBLE] = 0;
	expanded_str = ft_new_str(0);
	i = -1;
	while (str[++i])
	{
		if (quote_need_remove(in_quote, str[i]))
			continue ;
		if (is_need_expand(str + i, in_quote))
			expanded_str = ft_strjoin(expanded_str, \
			expand_env(env_list, str, &i), free, free);
		else
			expanded_str = ft_str_append(expanded_str, str[i], free);
	}
	return (expanded_str);
}

// token list 돌면서 각 토큰마다 expand_string() 함수 적용
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

static int	is_need_expand(char *str, int *in_quote)
{
	if (*str != '$')
		return (0);
	if (in_quote[SINGLE])
		return (0);
	str++;
	if (!(*str))
		return (0);
	if (ft_isspace(*str))
		return (0);
	if (!ft_isalnum(*str) && !ft_isspecific(*str))
		return (0);
	return (1);
}

static char	*expand_env(t_list *env_list, char *str, int *i)
{
	char	*env_value;
	char	*key;
	int		start;

	if (!env_list)
		return (str);
	if (!str || !i)
		return (0);
	start = ++(*i);
	if (str[start] == '?')
		return (ft_itoa(g_exit_code));
	if (ft_isdigit(str[start]) || ft_isspecific(str[start]))
		return (0);
	while (str[*i] && ft_isalnum(str[*i]))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	env_value = get_env_value(env_list, key);
	free(key);
	(*i)--;
	return (ft_strdup(env_value));
}
