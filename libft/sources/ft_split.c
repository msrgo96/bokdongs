/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:45:19 by jooahn            #+#    #+#             */
/*   Updated: 2023/12/13 16:24:05 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*get_word(char const *s, char c);
static int	get_word_cnt(char const *s, char c);
static char	**free_arr(char **arr, int len);

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*word;
	int		word_cnt;
	int		i;

	word_cnt = get_word_cnt(s, c);
	result = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!result)
		exit(ERR_MALLOC);
	i = 0;
	while (i < word_cnt)
	{
		while (*s && (*s == c))
			s++;
		word = get_word(s, c);
		if (!word)
			return (free_arr(result, i));
		result[i] = word;
		s += ft_strlen(word);
		i++;
	}
	result[word_cnt] = 0;
	return (result);
}

void	ft_split_free(char **s)
{
	int	idx;

	idx = 0;
	while (s[idx])
	{
		free(s[idx]);
		idx++;
	}
	free(s);
}

static char	*get_word(char const *s, char c)
{
	char	*word;
	size_t	len;
	size_t	i;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	len = i;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		exit(ERR_MALLOC);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = 0;
	return (word);
}

static int	get_word_cnt(char const *s, char c)
{
	int		cnt;
	size_t	i;
	int		flag;

	cnt = 0;
	i = 0;
	flag = 1;
	while (s[i])
	{
		if ((s[i] != c) && flag)
		{
			cnt++;
			flag = 0;
		}
		else if ((s[i] == c) && !flag)
			flag = 1;
		i++;
	}
	return (cnt);
}

static char	**free_arr(char **arr, int cnt)
{
	int		i;

	i = 0;
	while (i < cnt)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ((char **)0);
}
