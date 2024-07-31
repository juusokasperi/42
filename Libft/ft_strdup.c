/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:35:06 by jrinta-           #+#    #+#             */
/*   Updated: 2024/07/31 23:43:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	char	*dest_ptr;

	dest = (char *)malloc((ft_strlen(s1) + 1));
	if (!dest)
		return (NULL);
	dest_ptr = dest;
	while (*s1)
		*dest_ptr++ = *s1++;
	*dest_ptr = '\0';
	return (dest);
}
