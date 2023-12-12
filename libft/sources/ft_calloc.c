/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:00:33 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/12 22:20:42 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > FT_LONG_MAX / size)
		return (0);
	pointer = (void *)malloc(count * size);
	if (!pointer)
		ft_exit_with_msg(ERR_MALLOC);
	ft_bzero(pointer, count * size);
	return (pointer);
}
