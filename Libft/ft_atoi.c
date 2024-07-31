/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:11:39 by jrinta-           #+#    #+#             */
/*   Updated: 2024/07/31 23:42:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	issign(int c, int *s)
{
	if (c == '-' || c == '+')
	{
		if (c == '-')
			*s = -(*s);
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	s = 1;
	i = 0;
	res = 0;
	while (isspace(str[i]))
		i++;
	if (issign(str[i], &s))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (s * res);
}
