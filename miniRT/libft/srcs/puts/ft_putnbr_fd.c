/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:09:48 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/22 15:57:24 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr_fd(int n, int fd)
{
	char	digit;
	int		count;

	count = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	else if (n < 0)
	{
		count += write(fd, "-", 1);
		n = -n;
		count += ft_putnbr_fd(n, fd);
	}
	else
	{
		if (n >= 10)
			count += ft_putnbr_fd(n / 10, fd);
		digit = n % 10 + '0';
		count += write(fd, &digit, 1);
	}
	return (count);
}
