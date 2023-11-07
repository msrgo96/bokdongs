/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:39:48 by jooahn            #+#    #+#             */
/*   Updated: 2023/09/01 19:54:09 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	free_and_return(char *data)
{
	if (data)
		free(data);
	return (0);
}

char	*ft_strcat(char *s, char *buffer, ssize_t size)
{
	char	*result;
	char	*p;
	size_t	i;

	if (!buffer || size == 0)
		return (s);
	result = (char *)malloc(ft_strlen(s) + size + 1);
	if (!result)
	{
		if (s)
			free(s);
		return (0);
	}
	p = result;
	i = 0;
	while (s && s[i])
		*p++ = s[i++];
	if (s)
		free(s);
	p[size] = 0;
	while (size-- > 0)
		p[size] = buffer[size];
	return (result);
}

ssize_t	ft_strchr_idx(char *s, char c, size_t offset)
{
	size_t	i;

	if (!s)
		return (-1);
	i = offset;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (-1);
}

// size_t	ft_strlen(char *s)
// {
// 	size_t	len;

// 	if (!s)
// 		return (0);
// 	len = 0;
// 	while (*s++)
// 		len++;
// 	return (len);
// }
