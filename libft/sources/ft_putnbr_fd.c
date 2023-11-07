/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:07:56 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/31 19:36:51 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	number[12];
	int		len;
	int		i;
	int		digit;

	len = ft_intlen(n);
	number[len] = 0;
	i = 0;
	if (n < 0)
	{
		number[0] = '-';
		i = 1;
	}
	while (--len >= i)
	{
		digit = n % 10;
		if (digit < 0)
			digit *= -1;
		number[len] = digit + '0';
		n /= 10;
	}
	return (ft_putstr_fd(number, fd));
}
