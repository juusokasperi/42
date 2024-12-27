/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:11:39 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/09 00:37:34 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_overflow(int c, long res)
{
	return ((res >= LONG_MAX / 10)
		&& (res > LONG_MAX / 10 || (c - '0') > LONG_MAX % 10));
}

int	ft_atoi(const char *str)
{
	int		s;
	long	res;

	s = 1;
	res = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			s *= -1;
	while (ft_isdigit(*str))
	{
		if (check_overflow(*str, res))
		{
			if (s == 1)
				return (-1);
			else
				return (0);
		}
		res = res * 10 + (*str - '0');
		str++;
	}
	return ((int)(res * s));
}
