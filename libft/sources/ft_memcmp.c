/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 04:40:39 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/21 03:34:14 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		diff;	

	i = 0;
	diff = 0;
	while (i < n)
	{
		diff = (int)*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i);
		if (diff != 0)
			break ;
		i++;
	}
	return (diff);
}
