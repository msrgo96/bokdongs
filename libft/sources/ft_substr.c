/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 21:45:36 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/12 22:24:00 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	min(size_t size1, size_t size2);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;
	size_t	sub_len;

	s_len = ft_strlen(s);
	if (s_len <= (size_t)start)
	{
		substr = (char *)malloc(sizeof(char));
		if (!substr)
			ft_exit_with_msg(ERR_MALLOC);
		*substr = 0;
		return (substr);
	}
	sub_len = min(s_len - start, len);
	substr = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (!substr)
		ft_exit_with_msg(ERR_MALLOC);
	substr[sub_len] = 0;
	while (sub_len-- > 0)
		substr[sub_len] = s[(size_t)start + sub_len];
	return (substr);
}

static size_t	min(size_t size1, size_t size2)
{
	if (size1 < size2)
		return (size1);
	return (size2);
}
