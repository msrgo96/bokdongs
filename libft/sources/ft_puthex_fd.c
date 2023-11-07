/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:58:00 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/31 19:36:35 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_puthex_fd(size_t n, int is_upper, int fd)
{
	char	hex_num[17];
	int		len;
	int		i;
	char	hex;

	len = ft_ullen(n, 16);
	hex_num[len] = 0;
	i = len;
	while (--i >= 0)
	{
		hex = FT_HEX[n % 16];
		if (is_upper)
			hex = ft_toupper(hex);
		hex_num[i] = hex;
		n /= 16;
	}
	return (write(fd, hex_num, len));
}
