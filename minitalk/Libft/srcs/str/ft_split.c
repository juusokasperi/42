/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:24:12 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 19:27:02 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_separator(char c, char sep)
{
	return (c == sep || c == '\0');
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_separator(s[i + 1], c)
			&& !is_separator(s[i], c))
			count++;
		i++;
	}
	return (count);
}

static char	*copy_str(char const *src, int len)
{
	char	*dest;
	int		i;

	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	fill_array(char **array, const char *s, char c)
{
	int		i;
	int		cell;

	cell = 0;
	while (*s)
	{
		if (!is_separator(*s, c))
		{
			i = 0;
			while (s[i] && !is_separator(s[i], c))
				i++;
			array[cell] = copy_str(s, i);
			if (!array[cell])
			{
				while (cell > 0)
					free(array[--cell]);
				return (0);
			}
			cell++;
			s += i;
		}
		else
			s++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		substr_count;

	if (!s)
		return (NULL);
	substr_count = count_words(s, c);
	array = (char **)malloc((substr_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (!fill_array(array, s, c))
	{
		free(array);
		return (NULL);
	}
	array[substr_count] = NULL;
	return (array);
}
