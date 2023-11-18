/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 23:06:52 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/18 23:33:15 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_str_append(char *s, char c);

char	*expand_env(char *str)
{
	int		in_quotes[2];
	char	*new_str;
	int		i;
	int		j;

	in_quotes[SINGLE] = 0;
	in_quotes[DOUBLE] = 0;
	i = -1;
	j = 0;
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
		if (str[i] == '$' && !in_quotes[SINGLE])
			//
		else
			ft_str_append(new_str, str[j]);
		j++;
	}
}

static char	*ft_str_append(char *s, char c)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!new_str)
		exit(EXIT_FAILURE);
	i = 0;
	while (*s)
	{
		new_str[i++] = s[i];
		s++;
	}
	new_str[i++] = c;
	new_str[i] = 0;
	free(s);
	return (new_str);
}
