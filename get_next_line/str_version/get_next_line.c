/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:26:33 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/17 19:10:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_strs(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (0);
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
	len = (ptr - str) + 1;
	line = ft_substr(str, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_buffer(int fd, char *str)
{
	int		i;
	char	*buffer;

	i = 1;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_str(&str));
	buffer[0] = '\0';
	while (i > 0 && !ft_strchr(buffer, '\n'))
	{
		i = read (fd, buffer, BUFFER_SIZE);
		if (i > 0)
		{
			buffer[i] = '\0';
			str = join_strs(str, buffer);
		}
	}
	free(buffer);
	if (i == -1)
		return (free_str(&str));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*new_line;

	if (fd < 0)
		return (NULL);
	if ((str && !ft_strchr(str, '\n')) || !str)
		str = read_buffer (fd, str);
	if (!str)
		return (NULL);
	new_line = fetch_line(str);
	if (!new_line)
		return (free_str(&str));
	str = clean_str(str);
	return (new_line);
}
