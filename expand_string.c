/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:06:52 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/22 22:02:45 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(int in_quotes[2], char **expanded_str, int *i);
static int	has_skip_quote(int in_quotes[2], char c);
static int	find_env(char *str, int in_quotes[2]);
static char	*expand_env(t_list *env_list, char *str, int *i);

char	*expand_string(t_list *env_list, char *str, void (*del)(void *))
{
	int		in_quotes[2];
	char	*expanded_str;
	int		i;

	init_data(in_quotes, &expanded_str, &i);
	while (str[++i])
	{
		if (has_skip_quote(in_quotes, str[i]))
			continue ;
		if (find_env(str + i, in_quotes))
			expanded_str = ft_strjoin(expanded_str, \
			expand_env(env_list, str, &i), free, ft_none);
		else
			expanded_str = ft_str_append(expanded_str, str[i], free);
	}
	del(str);
	return (expanded_str);
}

static void	init_data(int in_quotes[2], char **expanded_str, int *i)
{
	in_quotes[SINGLE] = 0;
	in_quotes[DOUBLE] = 0;
	*i = -1;
	*expanded_str = ft_new_str(0);
}

static int	has_skip_quote(int in_quotes[2], char c)
{
	if (c == '\'' && !in_quotes[DOUBLE])
	{
		in_quotes[SINGLE] ^= 1;
		return (1);
	}
	if (c == '\"' && !in_quotes[SINGLE])
	{
		in_quotes[DOUBLE] ^= 1;
		return (1);
	}
	return (0);
}

static int	find_env(char *str, int in_quotes[2])
{
	if (*str == '$' && *(str + 1) && !in_quotes[SINGLE])
		return (1);
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
