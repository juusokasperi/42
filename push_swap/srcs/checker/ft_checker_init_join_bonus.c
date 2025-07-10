/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_init_join_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:49:16 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/05 01:44:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static char	*copy_str(char *src);
static int	copy_values(char **joined_values, char **values, int i);
static int	fill_values(char **joined_values, char **values, char **new_values);
static int	count_elements(char **values, char **new_values);

char	**ft_join(char **values, char **new_values)
{
	int		total_count;
	char	**joined_values;

	total_count = count_elements(values, new_values);
	joined_values = ft_calloc(total_count + 1, sizeof(char *));
	if (!joined_values)
		return ((char **)ft_free_split(values, new_values));
	if (!fill_values(joined_values, values, new_values))
	{
		free(joined_values);
		return ((char **)ft_free_split(values, new_values));
	}
	ft_free_split(values, new_values);
	return (joined_values);
}

static char	*copy_str(char *src)
{
	char	*dest;
	size_t	i;
	size_t	len;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
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

static int	copy_values(char **joined_values, char **values, int i)
{
	int	j;

	j = 0;
	while (values[j])
	{
		joined_values[i] = copy_str(values[j]);
		if (!joined_values[i])
		{
			while (i > 0)
				free(joined_values[i--]);
			return (-1);
		}
		i++;
		j++;
	}
	return (i);
}

static int	fill_values(char **joined_values, char **values, char **new_values)
{
	int	i;

	i = 0;
	if (values)
	{
		i = copy_values(joined_values, values, i);
		if (i == -1)
			return (0);
	}
	if (new_values)
	{
		i = copy_values(joined_values, new_values, i);
		if (i == -1)
			return (0);
	}
	return (1);
}

static int	count_elements(char **values, char **new_values)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (values)
	{
		while (values[i])
		{
			count++;
			i++;
		}
	}
	i = 0;
	if (new_values)
	{
		while (new_values[i])
		{
			count++;
			i++;
		}
	}
	return (count);
}
