/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:06:52 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/20 16:47:34 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_str_append(char *s, char c);

char	*expand_env(t_list *env_list, char *str)
{
	int		in_quotes[2];
	char	*new_str;
	int		i;
	int		start;

	in_quotes[SINGLE] = 0;
	in_quotes[DOUBLE] = 0;
	i = -1;
	new_str = (char *)malloc(sizeof(char) * 1);
	if (!new_str)
		exit(EXIT_FAILURE);
	new_str[0] = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !in_quotes[DOUBLE])
		{
			in_quotes[SINGLE] ^= 1;
			continue ;
		}
		if (str[i] == '\"' && !in_quotes[SINGLE])
		{
			in_quotes[DOUBLE] ^= 1;
			continue ;
		}
		if (str[i] == '$' && str[i + 1] && !in_quotes[SINGLE])
		{
			i++;
			start = i;
			char *temp;
			if (ft_isalnum(str[i]))
				while (str[i] && ft_isalnum(str[i]))
					i++;
			else
				i++;
			temp = get_env_value(env_list, ft_substr(str, start, i - start));
			new_str = ft_strjoin(new_str, temp);
			i--;
		}
		else
			new_str = ft_str_append(new_str, str[i]);
	}
	return (new_str);
}

char	*get_env_value(t_list *env_list, char *key)
{
	t_node	*node;

	if (!env_list || !key)
		return (0);
	node = env_list->head;
	while (node)
	{
		if (ft_str_is_same(((t_env *)node->content)->key, key))
			return (((t_env *)node->content)->value);
		node = node->next;
	}
	return (0);
}

static char	*ft_str_append(char *s, char c)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!new_str)
		exit(EXIT_FAILURE);
	i = 0;
	while (s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = 0;
	//free(s);
	return (new_str);
}
