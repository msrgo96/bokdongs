/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 00:39:53 by jooahn            #+#    #+#             */
/*   Updated: 2023/10/20 23:55:58 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_node **lst, t_node *new)
{
	if (!lst || !new)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		(*lst)->prv = new;
		new->next = *lst;
		new->prv = NULL;
		*lst = new;
	}
}
