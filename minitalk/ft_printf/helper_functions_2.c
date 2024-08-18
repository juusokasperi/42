/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:35:10 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/18 12:39:05 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*str_dup(const char *s1)
{
	char	*dest;
	char	*dest_ptr;

	dest = (char *)malloc((str_len(s1) + 1));
	if (!dest)
		return (NULL);
	dest_ptr = dest;
	while (*s1)
		*dest_ptr++ = *s1++;
	*dest_ptr = '\0';
	return (dest);
}

size_t	str_len(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}
