/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:48:59 by jrinta-           #+#    #+#             */
/*   Updated: 2024/07/31 22:22:05 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	if (!src || !dst)
		return (0);
	if (dstsize > 0)
	{
		i = 0;
		while (i < dstsize - 1)
		{
			if (src[i])
				dst[i] = src[i];
			else
				dst[i] = 0;
			i++;
		}
		dst[i] = 0;
	}
	return (ft_strlen(src));
}
