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

static void	init_data(int *i, int *start, int *in_quote);

/* 
split str to list include separator & ignore separator in quote
return : string list
*/
t_list	*split_include_separator(char *s, const char *sep)
{
	t_list	*list;
	int		i;
	int		start;
	int		in_quote[2];

	list = ft_new_list();
	init_data(&i, &start, in_quote);
	while (s[++i])
	{
		if (is_in_quote(s[i], in_quote))
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

/*
split str to list exclude separator & ignore separator in quote
return : string list
*/
t_list	*split_exclude_separator(char *s)
{
	t_list	*list;
	int		i;
	int		start;
	int		in_quote[2];

	list = ft_new_list();
	init_data(&i, &start, in_quote);
	while (s[++i])
	{
		if (is_in_quote(s[i], in_quote) || !ft_isspace(s[i]))
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

static void	init_data(int *i, int *start, int *in_quote)
{
	*i = -1;
	*start = 0;
	in_quote[SINGLE] = 0;
	in_quote[DOUBLE] = 0;
}
