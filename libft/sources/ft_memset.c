/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:09:24 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/21 03:38:21 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	value;
	size_t			i;

	value = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		*((unsigned char *)b + i) = value;
		i++;
	}
	return (b);
}
