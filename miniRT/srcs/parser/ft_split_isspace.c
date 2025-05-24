/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_isspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:26:18 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/02 20:21:58 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static char	**count_words(char const *s, int *word_count)
{
	char	**result;
	int		i;

	*word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
			(*word_count)++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	result = (char **)malloc(sizeof(char *) * ((*word_count) + 1));
	return (result);
}

static bool	fill_result(char const *s, char **result)
{
	int		i;
	int		start;
	int		count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && !ft_isspace(s[i]))
				i++;
			result[count] = ft_substr(s, start, i - start);
			if (!result[count])
				return (false);
			count++;
		}
	}
	result[count] = NULL;
	return (true);
}

char	**ft_split_isspace(char const *s)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	result = count_words(s, &word_count);
	if (!result)
		return (NULL);
	if (!fill_result(s, result))
	{
		free_split(result);
		return (NULL);
	}
	return (result);
}
