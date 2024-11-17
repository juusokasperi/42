/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:26:33 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/17 19:09:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*join_strs(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (free_str(&s1));
	i = 0;
	j = 0;
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
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
		return (free_str(&str));
	start = (ptr - str) + 1;
	if (!str[start])
		return (free_str(&str));
	new = ft_substr(str, start, ft_strlen(str) - start);
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
		return (free_str(&str));
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
		return (free_str(&str));
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
		return (free_str(&str[fd]));
	str[fd] = clean_str(str[fd]);
	return (new_line);
}
