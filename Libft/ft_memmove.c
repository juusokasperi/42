/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:27:49 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/31 11:33:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;

	dst_p = (unsigned char *)dst;
	src_p = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst_p > src_p)
		while (len-- > 0)
			dst_p[len] = src_p[len];
	else
		ft_memcpy(dst, src_p, len);
	return (dst);
}
