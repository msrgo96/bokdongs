/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:58:35 by jooahn            #+#    #+#             */
/*   Updated: 2023/10/20 23:55:49 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*last;

	if (!lst)
		return ;
	last = ft_lstlast(*lst);
	if (last == 0)
		(*lst = new);
	else
	{
		last->next = new;
		new->prv = last;
		new->next = NULL;
	}
}
