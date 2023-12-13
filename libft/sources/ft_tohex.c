/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tohex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:20:07 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/13 16:24:05 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_tohex(size_t n, int is_upper)
{
	char	*hex_num;
	int		len;
	char	hex;

	len = ft_ullen(n);
	hex_num = (char *)malloc(sizeof(char) * (len + 1));
	if (!hex_num)
		exit(ERR_MALLOC);
	hex_num[len] = 0;
	while (--len >= 0)
	{
		hex = FT_HEX[n % 16];
		if (is_upper)
			hex = ft_toupper(hex);
		hex_num[len] = hex;
		n /= 16;
	}
	return (hex_num);
}
