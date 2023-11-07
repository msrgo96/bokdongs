/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:56:59 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/21 03:41:38 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;

	idx = 0;
	while (idx < n)
	{
		if ((unsigned char)s1[idx] > (unsigned char)s2[idx])
			return (1);
		else if ((unsigned char)s1[idx] < (unsigned char)s2[idx])
			return (-1);
		if (s1[idx] == 0 || s2[idx] == 0)
			break ;
		idx++;
	}
	return (0);
}
