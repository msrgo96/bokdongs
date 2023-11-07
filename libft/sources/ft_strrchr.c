/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:53:18 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/21 23:04:30 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	last_idx;

	last_idx = ft_strlen(s);
	while (1)
	{
		if (s[last_idx] == (char)c)
			return ((char *)s + last_idx);
		if (last_idx == 0)
			break ;
		last_idx--;
	}
	return (0);
}
