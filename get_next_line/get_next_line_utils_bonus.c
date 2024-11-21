/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:55:36 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/17 18:36:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*free_str(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*s;
	unsigned char	*p;
	size_t			total_size;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	s = malloc(total_size);
	if (!s)
		return (NULL);
	p = (unsigned char *)s;
	while (total_size--)
		p[total_size] = 0;
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = 0;
	return (substr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}
