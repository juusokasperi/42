/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:35:06 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 18:25:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*dest_ptr;

	dest = (char *)malloc((ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	dest_ptr = dest;
	while (*s)
		*dest_ptr++ = *s++;
	*dest_ptr = '\0';
	return (dest);
}
