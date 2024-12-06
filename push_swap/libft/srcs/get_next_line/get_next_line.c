/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:26:33 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/06 01:51:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_strs(char *s1, char *s2)
{
	char	*result;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	result = ft_strjoin(s1, s2);
	if (!result)
		return (ft_free(&s1));
	free(s1);
	return (result);
}

char	*clean_str(char *str)
{
	char	*new;
	char	*ptr;
	int		start;

	ptr = ft_strchr(str, '\n');
	if (!ptr)
		return (ft_free(&str));
	start = (ptr - str) + 1;
	if (!str[start])
		return (ft_free(&str));
	new = ft_substr(str, start, ft_strlen(str) - start);
	ft_free(&str);
	if (!new)
		return (NULL);
	return (new);
}

char	*fetch_line(char *str)
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
	if (!line)
		return (NULL);
	return (line);
}

char	*read_buffer(int fd, char *str)
{
	int		nb_read;
	char	*buffer;

	nb_read = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (ft_free(&str));
	while (!str || !ft_strchr(str, '\n'))
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read <= 0)
			break ;
		buffer[nb_read] = '\0';
		str = join_strs(str, buffer);
		if (!str)
			break ;
	}
	free(buffer);
	if (nb_read == -1)
		return (ft_free(&str));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if ((str[fd] && !ft_strchr(str[fd], '\n')) || !str[fd])
		str[fd] = read_buffer(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	new_line = fetch_line(str[fd]);
	if (!new_line)
		return (ft_free(&str[fd]));
	str[fd] = clean_str(str[fd]);
	return (new_line);
}
