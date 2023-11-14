/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:55:10 by jooahn            #+#    #+#             */
/*   Updated: 2023/11/14 19:46:24 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ls -al > a.txt | echo -n"test |><<<" > test.txt

// (ls -al > a.txt) (|) (echo -n"test |><<<" > test.txt)

// (ls -al) (>) (a.txt) (|) (echo -n"test |><<<") (>) (test.txt)

// (ls) (-al) (>) (a.txt) (|) (echo) (-n"test |><<<") (>) (test.txt)

// input null_pointer 체크는 밖의 main에서
t_list	*tokenizer(char *input)
{

}
