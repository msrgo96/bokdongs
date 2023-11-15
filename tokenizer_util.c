/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:53:38 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/15 23:16:32 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SINGLE 0
#define DOUBLE 1
static void	init_data(int *i, int *start, int *in_quotes);

// "",''안의 separator 무시, list로 반환, 구분자 포함 : char *
t_list	*ft_split2(char *s, const char *sep)
{
	t_list	*list;
	int		i;
	int		start;
	int		in_quotes[2];

	list = ft_newlist();
	init_data(&i, &start, in_quotes);
	while (s[++i])
	{
		if (s[i] == '\'')
			in_quotes[SINGLE] ^= 1;
		else if (s[i] == '\"')
			in_quotes[DOUBLE] ^= 1;
		if (in_quotes[SINGLE] || in_quotes[DOUBLE])
			continue ;
		if (ft_strncmp(s + i, sep, ft_strlen(sep)) == 0)
		{
			if (start != i)
				lst_add(list, ft_newnode(ft_substr(s, start, i - start)));
			lst_add(list, ft_newnode(ft_strdup(sep)));
			i += (ft_strlen(sep) - 1);
			start = i + 1;
		}
	}
	if (start != i)
		lst_add(list, ft_newnode(ft_substr(s, start, i - start)));
	return (list);
}

// "",''안의 separator 무시, list로 반환, 구분자 무시
t_list	*ft_split3(char *s)
{
	t_list	*list;
	int		i;
	int		start;
	int		in_quotes[2];

	list = ft_newlist();
	init_data(&i, &start, in_quotes);
	while (s[++i])
	{
		if (s[i] == '\'')
			in_quotes[SINGLE] ^= 1;
		else if (s[i] == '\"')
			in_quotes[DOUBLE] ^= 1;
		if (in_quotes[SINGLE] || in_quotes[DOUBLE])
			continue ;
		if (ft_isspace(s[i]))
		{
			if (start != i)
				lst_add(list, ft_newnode(ft_substr(s, start, i - start)));
			while (s[i] && ft_isspace(s[i]))
				i++;
			start = i;
			i--;
		}
	}
	if (start != i)
		lst_add(list, ft_newnode(ft_substr(s, start, i - start)));
	return (list);
}

static void	init_data(int *i, int *start, int *in_quotes)
{
	*i = -1;
	*start = 0;
	in_quotes[SINGLE] = 0;
	in_quotes[DOUBLE] = 0;
}

void	print_content(void *content)
{
	printf("content : @%s@\n", (char *)content);
}
