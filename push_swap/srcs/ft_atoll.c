/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:11:39 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/27 11:40:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Convert string to long long,
// return a value over MAX INT if the
// string contains non-digit characters

static int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

long long int	ft_atoll(const char *str)
{
	int			s;
	long long	res;

	s = 1;
	res = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			s *= -1;
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * s);
}