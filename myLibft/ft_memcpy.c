/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:07:00 by jrinta-           #+#    #+#             */
/*   Updated: 2024/07/31 22:22:34 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;
	size_t			i;

	dst_p = (unsigned char *)dst;
	src_p = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_p[i] = src_p[i];
		i++;
	}
	return (dst);
}
