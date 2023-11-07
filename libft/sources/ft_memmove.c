/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 04:29:39 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/21 22:28:37 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;
	size_t	i_r;

	if (dest == 0 && src == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		if ((size_t)dest > (size_t)src)
		{
			i_r = len - 1 - i;
			*((unsigned char *)dest + i_r) = *((unsigned char *)src + i_r);
		}
		else
			*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dest);
}
