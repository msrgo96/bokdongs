/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_err_msg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:07:38 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/12 22:47:02 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_err_msg(int error_code)
{
	ft_printf((const char *)get_err_msg(error_code));
}

char	*get_err_msg(int error_code)
{
	if (error_code == ERR_MALLOC)
		return ("malloc failed\n");
	return ("unknown error\n");
}
