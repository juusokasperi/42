/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:35:56 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 19:42:11 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	str_len;

	str_len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)(s + str_len));
	while (str_len--)
		if (s[str_len] == (char)c)
			return ((char *)(s + str_len));
	return (NULL);
}
