/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:26:33 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/15 20:27:17 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append(char *new_line, char *buffer);
static void	clean_buffer(char *buffer);
static char	*fetch_line(char *str);
static char	*read_buffer(int fd, char *new_line, char *buffer);

char	*get_next_line(int fd)
{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	new_line = NULL;
	new_line = read_buffer(fd, new_line, buffer[fd]);
	if (!new_line)
		return (ft_free((void **)&new_line));
	new_line = fetch_line(new_line);
	if (!new_line)
		return (ft_free((void **)&new_line));
	clean_buffer(buffer[fd]);
	return (new_line);
}

static char	*append(char *new_line, char *buffer)
{
	char	*result;

	if (!new_line)
	{
		new_line = ft_calloc(1, 1);
		if (!new_line)
			return (NULL);
	}
	result = ft_strjoin(new_line, buffer);
	if (!result)
		return (ft_free((void **)&new_line));
	ft_free((void **)&new_line);
	return (result);
}

static void	clean_buffer(char *buffer)
{
	char	*ptr;
	int		start;

	ptr = ft_strchr(buffer, '\n');
	if (!ptr)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		return ;
	}
	start = (ptr - buffer) + 1;
	ft_memmove(buffer, buffer + start, ft_strlen(buffer + start) + 1);
	ft_bzero(buffer + ft_strlen(buffer), BUFFER_SIZE - ft_strlen(buffer));
}

static char	*fetch_line(char *str)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(str, '\n');
	if (!ptr)
		len = ft_strlen(str);
	else
		len = (ptr - str) + 1;
	line = ft_substr(str, 0, len);
	ft_free((void **)&str);
	if (!line)
		return (NULL);
	return (line);
}

static char	*read_buffer(int fd, char *new_line, char *buffer)
{
	int		nb_read;

	if (buffer[0])
	{
		new_line = append(new_line, buffer);
		if (!new_line)
			return (NULL);
	}
	nb_read = 1;
	while (!new_line || !ft_strchr(new_line, '\n'))
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read <= 0)
			break ;
		buffer[nb_read] = '\0';
		new_line = append(new_line, buffer);
		if (!new_line)
			break ;
	}
	if (nb_read == -1)
		return (ft_free((void **)&new_line));
	return (new_line);
}
