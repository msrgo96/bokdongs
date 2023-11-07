/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:38:20 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/31 20:13:42 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int	ft_putptr_fd(void *ptr, int fd)
{
	int		len;
	size_t	addr;

	len = write(fd, "0x", 2);
	if (len < 0)
		return (len);
	addr = (size_t)ptr;
	len = ft_puthex_fd(addr, 0, fd);
	if (len < 0)
		return (len);
	return (len + 2);
}
