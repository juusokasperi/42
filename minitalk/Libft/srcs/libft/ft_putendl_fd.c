/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:08:27 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/22 15:37:07 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putendl_fd(char *s, int fd)
{
	int	count_str;
	int	count_nl;

	if (!s)
		return (write (fd, "\n", 1));
	count_str = write(fd, s, ft_strlen(s));
	if (count_str == -1)
		return (-1);
	count_nl = write(fd, "\n", 1);
	if (count_nl == -1)
		return (-1);
	return (count_str + count_nl);
}
