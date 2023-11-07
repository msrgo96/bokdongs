/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:51:48 by jooahn            #+#    #+#             */
/*   Updated: 2023/08/23 00:03:01 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum(char *input)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	if (input[idx] == '-' || input[idx] == '+')
		idx++;
	while (input[idx])
	{
		if (!ft_isdigit(input[idx]))
			return (0);
		flag = 1;
		idx++;
	}
	return (flag);
}
