/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:32:06 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/12 22:23:35 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*result;

	len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		ft_exit_with_msg(ERR_MALLOC);
	result[len] = 0;
	i = 0;
	while (i < len)
	{
		result[i] = f((unsigned int)i, s[i]);
		i++;
	}
	return (result);
}
