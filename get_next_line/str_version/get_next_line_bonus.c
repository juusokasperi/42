/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:26:33 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/15 14:28:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*join_strs(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free_str(&s1));
	i = 0;
	while (s1[i++])
	{
		write(1, i, 1);
		str[i] = s1[i];
	}
	j = 0;
	while (s2[j++])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*clean_str(char *str)
{
	char	*new;
	char	*ptr;
	int		len;

	ptr = ft_strchr(str, '\n');
	if (!ptr)
	{
		new = NULL;
		return (free_str(&str));
	}
	else
		len = (ptr - str) + 1;
	if (!str[len])
		return (free_str(&str));
	new = ft_substr(str, len, ft_strlen(str) - len);
	free_str(&str);
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
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_str(&str));
	buffer[0] = '\0';
	while (nb_read > 0 && !ft_strchr(buffer, '\n'))
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read > 0)
		{
			buffer[nb_read] = '\0';
			str = join_strs(str, buffer);
		}
	}
	free(buffer);
	if (nb_read == -1)
		return (free_str(&str));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[FOPEN_MAX];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((str[fd] && !ft_strchr(str[fd], '\n')) || !str[fd])
		str[fd] = read_buffer(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	new_line = fetch_line(str[fd]);
	if (!new_line)
		return (free_str(&str[fd]));
	str[fd] = clean_str(str[fd]);
	return (new_line);
}
