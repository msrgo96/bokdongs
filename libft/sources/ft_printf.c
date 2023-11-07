/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 17:54:29 by jooahn            #+#    #+#             */
/*   Updated: 2023/04/01 04:29:43 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

static int		check(const char *format, va_list ap);
static size_t	get_len(char specifier, va_list ap);
static int		putformat_fd(char specifier, va_list ap, int fd);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		temp;
	int		len;
	int		fd;

	va_start(ap, format);
	if (check(format, ap) < 0)
		return (-1);
	fd = 1;
	len = 0;
	while (*format)
	{
		if (*format == '%')
			temp = putformat_fd(*(++format), ap, fd);
		else
			temp = ft_putchar_fd(*format, fd);
		if (temp < 0)
			return (-1);
		len += temp;
		format++;
	}
	va_end(ap);
	return (len);
}

static int	putformat_fd(char specifier, va_list ap, int fd)
{
	if (specifier == 'c')
		return (ft_putchar_fd((char)va_arg(ap, int), fd));
	else if (specifier == 's')
		return (ft_putstr_fd(va_arg(ap, char *), fd));
	else if (specifier == 'p')
		return (ft_putptr_fd(va_arg(ap, void *), fd));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr_fd(va_arg(ap, int), fd));
	else if (specifier == 'u')
		return (ft_putunbr_fd(va_arg(ap, int), fd));
	else if (specifier == 'x')
		return (ft_puthex_fd(va_arg(ap, unsigned int), 0, fd));
	else if (specifier == 'X')
		return (ft_puthex_fd(va_arg(ap, unsigned int), 1, fd));
	else if (specifier == '%')
		return (ft_putchar_fd(specifier, fd));
	else
		return (0);
}

static int	check(const char *format, va_list ap)
{
	va_list		ap_copy;
	long long	len;

	va_copy(ap_copy, ap);
	len = 0;
	while (*format)
	{
		if (*format++ == '%')
			len += (long long)get_len(*format++, ap_copy);
		else
			len++;
		if (len >= FT_INT_MAX)
		{
			va_end(ap_copy);
			return (-1);
		}
	}
	va_end(ap_copy);
	return ((int)len);
}

static size_t	get_len(char specifier, va_list ap)
{
	char	*s;

	if (specifier == 'c')
	{
		va_arg(ap, int);
		return (1);
	}
	else if (specifier == 's')
	{
		s = va_arg(ap, char *);
		if (!s)
			return (ft_strlen("(null)"));
		return (ft_strlen(s));
	}
	else if (specifier == 'p')
		return (ft_ullen((size_t)va_arg(ap, void *), 16) + 2);
	else if (specifier == 'd' || specifier == 'i')
		return (ft_intlen(va_arg(ap, int)));
	else if (specifier == 'u')
		return (ft_ullen((unsigned int)va_arg(ap, int), 10));
	else if (specifier == 'x' || specifier == 'X')
		return (ft_ullen(va_arg(ap, unsigned int), 16));
	else if (specifier == '%')
		return (1);
	return (0);
}
