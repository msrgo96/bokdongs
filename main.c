/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moson <moson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:38:42 by moson             #+#    #+#             */
/*   Updated: 2023/11/07 15:38:43 by moson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	checkleak(void)
{
	system("leaks minishell");
}

int	main(void)
{
	char	*str;

	atexit(checkleak);
	while (1)
	{
		str = readline("$> ");
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			ft_free((void **)&str);
			break ;
		}
		if (str != NULL)
		{
			printf("stdin:%s\n", str);
			add_history(str);
			ft_free((void **)&str);
		}
	}
	return (0);
}
