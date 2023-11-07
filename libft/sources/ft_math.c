/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 02:36:18 by jooahn            #+#    #+#             */
/*   Updated: 2023/10/20 17:59:45 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	absolute(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

double	sqrt(double n)
{
	double	x_old;
	double	x_new;
	double	epsilon;

	x_old = n;
	x_new = 0.0;
	epsilon = 1e-10;
	while (1)
	{
		x_new = 0.5 * (x_old + n / x_old);
		if (absolute(x_new - x_old) < epsilon)
			break ;
		x_old = x_new;
	}
	return (x_new);
}
