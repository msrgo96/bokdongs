/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:29:05 by jooahn            #+#    #+#             */
/*   Updated: 2023/08/11 23:51:57 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	get_num(const char *str, int neg);

long	ft_strtol(const char *str)
{
	int	neg;

	neg = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		neg = 1;
		str++;
	}
	return (get_num(str, neg));
}

static long	get_num(const char *str, int neg)
{
	long	num;
	long	cutoff;
	char	cutlim;

	num = 0;
	cutoff = FT_LONG_MAX / 10;
	cutlim = FT_LONG_MAX % 10 + '0';
	while (ft_isdigit(*str))
	{
		if ((num > cutoff) || (num == cutoff && *str > cutlim))
		{
			if (neg)
				return (-FT_LONG_MAX - 1);
			return (FT_LONG_MAX);
		}
		num = (num * 10) + (*str - '0');
		str++;
	}
	if (neg)
		return (-num);
	return (num);
}
