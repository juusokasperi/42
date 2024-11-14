/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:26:33 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 22:01:56 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
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
	str[fd] = clean_str(str);
	return (new_line);
}
