/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:54:29 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/01 15:26:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	istrim(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
		if (c == set[i++])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	size_t			start;
	size_t			end;
	char			*new_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && istrim(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && istrim(s1[end - 1], set))
		end--;
	new_str = (char *)malloc(end - start + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < end - start)
	{
		new_str[i] = s1[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
