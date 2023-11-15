/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:23:03 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/15 23:16:34 by jooahn           ###   ########.fr       */
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
	t_list		*split_list;
	t_list		*sub_list;
	const char	*separators[5] = {"|", "<<", ">>", "<", ">"};

	split_list = ft_newlist();
	lst_add(split_list, ft_newnode(input));
	for (int i = 0; i < 6; i++)
	{
		t_node *node = split_list->head;
		while (node)
		{
			if (str_is_same(node->content, "|") || \
			str_is_same(node->content, "<<") || \
			str_is_same(node->content, ">>"))
			{
				node = node->next;
				continue ;
			}
			if (i == 5)
				sub_list = ft_split3(node->content);
			else
				sub_list = ft_split2(node->content, separators[i]);
			// if (node->prv)
			// {
			// 	sub_list->head->prv = node->prv;
			// 	node->prv->next = sub_list->head;
			// }
			// else
			// 	split_list->head = sub_list->head;
			// if (node->next)
			// {
			// 	sub_list->tail->next = node->next;
			// 	node->next->prv = sub_list->tail;
			// }
			// else
			// 	split_list->tail = sub_list->tail;
			free(sub_list);
			node = node->next;
		}
	}
	return (split_list);
}

// t_list	*list_split(t_list *list, char *separator)
// {
// 	t_node	*head;
// 	t_node	*tail;
// 	t_node	*node;

// 	head = list->head;
// 	tail = list->tail;
// 	node = head;
// 	while (node)
// 	{
// 		node = node->next;
// 	}
// }
