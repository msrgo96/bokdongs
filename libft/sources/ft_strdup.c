/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:02:10 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/13 16:24:05 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	idx;
	char	*dup;

	len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		exit(ERR_MALLOC);
	idx = 0;
	while (idx < len)
	{
		dup[idx] = s1[idx];
		idx++;
	}
	dup[idx] = 0;
	return (dup);
}
