/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str_to_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 15:34:47 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 16:31:54 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(int *i, int *start, int *in_quotes);

// "",''안의 separator 무시, list로 반환, 구분자 포함 : char *
t_list	*split_include_separator(char *s, const char *sep)
{
	t_list	*list;
	int		i;
	int		start;
	int		in_quotes[2];

	list = ft_new_list();
	init_data(&i, &start, in_quotes);
	while (s[++i])
	{
		if (is_in_quotes(s[i], in_quotes))
			continue ;
		if (ft_strncmp(s + i, sep, ft_strlen(sep)))
			continue ;
		add_word_in_list(list, s, i, &start);
		add_sep_in_list(list, sep, &i);
		start += ft_strlen(sep);
	}
	add_word_in_list(list, s, i, &start);
	return (list);
}

// "",''안의 separator 무시, list로 반환, 구분자 무시
t_list	*split_exclude_separator(char *s)
{
	t_list	*list;
	int		i;
	int		start;
	int		in_quotes[2];

	list = ft_new_list();
	init_data(&i, &start, in_quotes);
	while (s[++i])
	{
		if (is_in_quotes(s[i], in_quotes) || !ft_isspace(s[i]))
			continue ;
		add_word_in_list(list, s, i, &start);
		while (s[i] && ft_isspace(s[i]))
			i++;
		start = i;
		i--;
	}
	add_word_in_list(list, s, i, &start);
	return (list);
}

static void	init_data(int *i, int *start, int *in_quotes)
{
	*i = -1;
	*start = 0;
	in_quotes[SINGLE] = 0;
	in_quotes[DOUBLE] = 0;
}
