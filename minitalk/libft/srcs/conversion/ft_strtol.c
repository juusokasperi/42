/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 00:07:07 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/09 01:12:32 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_digits(const char **nptr, long *res, int base);
static void	check_sign(const char **nptr, int *sign);
static void	check_base(const char **nptr, int *base);

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	int		sign;
	long	res;

	if (!nptr)
		return (0);
	while (ft_isspace(*nptr))
		nptr++;
	check_sign(&nptr, &sign);
	check_base(&nptr, &base);
	if (base < 2 || base > 36)
		return (0);
	res = 0;
	if (!check_digits(&nptr, &res, base))
	{
		if (sign == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
	}
	if (endptr != NULL)
		*endptr = (char *)nptr;
	return (res * sign);
}

static int	check_digits(const char **nptr, long *res, int base)
{
	int	digit;

	while (**nptr)
	{
		if (ft_isdigit(**nptr))
			digit = **nptr - '0';
		else if (ft_isalpha(**nptr))
			digit = ft_tolower(**nptr) - 'a' + 10;
		else
			return (1);
		if (digit >= base)
			return (1);
		if (*res > (LONG_MAX - digit) / base)
			return (0);
		*res = *res * base + digit;
		(*nptr)++;
	}
	return (1);
}

static void	check_sign(const char **nptr, int *sign)
{
	if (**nptr == '-' || **nptr == '+')
	{
		if (**nptr == '-')
			*sign = -1;
		(*nptr)++;
	}
	else
		*sign = 1;
}

static void	check_base(const char **nptr, int *base)
{
	if (**nptr == '0' && (*(*nptr + 1) == 'x' || *(*nptr + 1) == 'X')
		&& (*base == 0 || *base == 16))
	{
		*base = 16;
		*nptr += 2;
	}
	else if (*base == 0 && **nptr == '0')
	{
		*base = 8;
		(*nptr)++;
	}
	else
		*base = 10;
}
