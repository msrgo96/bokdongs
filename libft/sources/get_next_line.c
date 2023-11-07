/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jooahn <jooahn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:38:21 by jooahn            #+#    #+#             */
/*   Updated: 2023/09/01 19:54:53 by jooahn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	load(char **data, char **saved_data);
static int	read_data(int fd, char **data, ssize_t *nl_idx);
static int	save(char *data, ssize_t nl_idx, char **saved_data);
static char	*get_line(char *data, ssize_t nl_idx, char **saved_data);

char	*get_next_line(int fd)
{
	static char	*saved_data = 0;
	char		*data;
	ssize_t		nl_idx;

	data = 0;
	if (!load(&data, &saved_data))
		return (0);
	if (!read_data(fd, &data, &nl_idx))
		return (0);
	if (!save(data, nl_idx, &saved_data))
		return (0);
	return (get_line(data, nl_idx, &saved_data));
}

static int	load(char **data, char **saved_data)
{
	size_t		i;
	size_t		len;

	if (*saved_data == 0)
		return (1);
	len = ft_strlen(*saved_data);
	*data = (char *)malloc(sizeof(char) * (len + 1));
	if (!*data)
	{
		free(*saved_data);
		*saved_data = 0;
		return (0);
	}
	(*data)[len] = 0;
	i = 0;
	while (i < len)
	{
		(*data)[i] = (*saved_data)[i];
		i++;
	}
	free(*saved_data);
	*saved_data = 0;
	return (1);
}

static int	read_data(int fd, char **data, ssize_t *nl_idx)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes;
	size_t	offset;

	*nl_idx = ft_strchr_idx(*data, '\n', 0);
	if (*nl_idx < 0)
		offset = ft_strlen(*data);
	while (*nl_idx < 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free_and_return(*data));
		if (bytes == 0)
			break ;
		*data = ft_strcat(*data, buffer, bytes);
		if (!*data)
			return (0);
		*nl_idx = ft_strchr_idx(*data, '\n', offset);
		offset += bytes;
	}
	return (1);
}

static int	save(char *data, ssize_t nl_idx, char **saved_data)
{
	size_t	i;
	size_t	len;

	if (nl_idx < 0)
		return (1);
	len = ft_strlen(data) - (nl_idx + 1);
	if (len == 0)
	{
		*saved_data = 0;
		return (1);
	}
	*saved_data = (char *)malloc(sizeof(char) * (len + 1));
	if (!(*saved_data))
		return (free_and_return(data));
	(*saved_data)[len] = 0;
	i = 0;
	while (i < len)
	{
		(*saved_data)[i] = data[(nl_idx + 1) + i];
		i++;
	}
	return (1);
}

static char	*get_line(char *data, ssize_t nl_idx, char **saved_data)
{
	ssize_t	i;
	char	*line;

	if (!data)
		return (0);
	if (nl_idx < 0)
		return (data);
	nl_idx++;
	line = (char *)malloc(sizeof(char) * (nl_idx + 1));
	if (!line)
	{
		free_and_return(*saved_data);
		*saved_data = 0;
		free_and_return(data);
		return (0);
	}
	line[nl_idx] = 0;
	i = 0;
	while (i < nl_idx)
	{
		line[i] = data[i];
		i++;
	}
	free(data);
	return (line);
}
