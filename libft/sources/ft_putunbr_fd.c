/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:22:34 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/31 20:14:10 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr_fd(unsigned int n, int fd)
{
	char	number[11];
	int		len;

	len = ft_ullen(n, 10);
	number[len] = 0;
	while (--len >= 0)
	{
		number[len] = (n % 10) + '0';
		n /= 10;
	}
	return (ft_putstr_fd(number, fd));
}
