/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:43:54 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/21 03:41:58 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	stack_i;
	size_t	need_i;

	if (*needle == 0)
		return ((char *)haystack);
	stack_i = 0;
	need_i = 0;
	while (stack_i < len)
	{
		if (haystack[stack_i] == 0)
			break ;
		if ((unsigned char)haystack[stack_i] == (unsigned char)needle[need_i])
			need_i++;
		else
		{
			stack_i -= (need_i);
			need_i = 0;
		}
		stack_i++;
		if (needle[need_i] == 0)
			return ((char *)(haystack + stack_i - need_i));
	}
	return (0);
}
