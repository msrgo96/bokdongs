/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:23:03 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/16 16:26:08 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// |ls   can  i<split>>?||

// 초기 데이터를 리스트로 만들고 넘기기
// 리스트를 받아서 노드 순회하며 안의 str들을 분리
// 첫번째애와 마지막 애를 기억해뒀다가 분리된 애들을 노드에 담아서 앞뒤로 연결
// 각 delimiter 기준으로 반복
t_list	*tokenizer(char *input)
{
	t_list		*base_list;
	const char	*separators[7] = {"|", "<<", ">>", "<", ">", " ", 0};
	int			i;

	base_list = ft_newlist();
	ft_list_append(base_list, ft_newnode(input));
	i = 0;
	while (separators[i])
	{
		split_list(base_list, separators[i]);
		i++;
	}
	return (base_list);
}

void	split_list(t_list *base_list, const char *separator)
{
	t_list	*sub_list;
	t_node	*node;
	t_node	*next;
	int		i;

	node = base_list->head;
	i = 0;
	while (node)
	{
		next = node->next;
		if (!ft_str_is_same(node->content, "<<") && !ft_str_is_same(node->content, ">>"))
		{
			if (ft_str_is_same((char *)separator, " "))
				sub_list = split_without_separator(node->content);
			else
				sub_list = split_with_separator(node->content, separator);
			if (ft_list_is_empty(sub_list))
			{
				ft_del_node_link(base_list, node, free);
				node = next;
				continue ;
			}
			int	size = ft_listsize(sub_list);
			ft_replace_node_with_list(base_list, sub_list, i);
			i += (size - 1);
		}
		node = next;
		i++;
	}
}
