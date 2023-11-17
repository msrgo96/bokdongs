/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:23:03 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/17 16:01:33 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		split_list_by_separator(t_list *base_list,
					const char *separator);
static t_list	*split_str_to_list(char *str, const char *separator);
static void		insert_list_at_node(t_list *base, t_list *sub, t_node *node);
static t_list	*wrap_in_token_list(t_list *string_list);

// readline으로 받은 문자열을 리스트로 만들기
// 리스트안의 각 노드들의 content를 separator 기준으로 분리
// 여러 separator에 대해 반복
t_list	*tokenizer(char *input)
{
	t_list		*string_list;
	int			i;
	const char	*separators[7] = {"|", "<<", ">>", "<", ">", " ", 0};

	i = 0;
	string_list = ft_new_list();
	ft_list_append(string_list, ft_new_node(input));
	while (separators[i])
		split_list_by_separator(string_list, separators[i++]);
	return (wrap_in_token_list(string_list));
}

static void	split_list_by_separator(t_list *base_list, const char *separator)
{
	t_list	*sub_list;
	t_node	*node;
	t_node	*next;

	node = base_list->head;
	while (node)
	{
		if (ft_str_is_same(node->content, "<<") || ft_str_is_same(node->content,
				">>"))
		{
			node = node->next;
			continue ;
		}
		next = node->next;
		sub_list = split_str_to_list(node->content, separator);
		insert_list_at_node(base_list, sub_list, node);
		node = next;
	}
}

static t_list	*split_str_to_list(char *str, const char *separator)
{
	if (ft_str_is_same((char *)separator, " "))
		return (split_exclude_separator(str));
	return (split_include_separator(str, separator));
}

static void	insert_list_at_node(t_list *base, t_list *sub, t_node *node)
{
	if (ft_list_is_empty(sub))
		ft_del_node_and_link(base, node, free);
	else
		ft_replace_node_with_list(base, sub, node);
}

static t_list	*wrap_in_token_list(t_list *string_list)
{
	return (ft_list_iter_reassign(string_list, (void *)wrap_in_token));
}
