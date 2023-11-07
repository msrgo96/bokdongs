/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:04:45 by jooahn            #+#    #+#             */
/*   Updated: 2023/03/31 19:36:12 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	temp;
	int	len;

	temp = write(fd, s, ft_strlen(s));
	if (temp < 0)
		return (temp);
	len = temp;
	temp = write(fd, "\n", 1);
	if (temp < 0)
		return (temp);
	len += temp;
	return (len);
}
