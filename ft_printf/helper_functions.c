/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 20:45:13 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/18 12:27:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	pad_width(int width, int size, int zero_pad)
{
	int	count;

	count = 0;
	while (width - size > 0)
	{
		if (zero_pad)
			count += print_c('0');
		else
			count += print_c(' ');
		width--;
	}
	return (count);
}

int	is_type(char c)
{
	if (c == '%' || c == 'c' || c == 's' || c == 'p' || c == 'i'
		|| c == 'd' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_spec(char c)
{
	if (c == '-' || c == '0' || c == '.' || c == '#'
		|| c == ' ' || c == '+' || c == '*')
		return (1);
	return (0);
}

int	is_flag(char c)
{
	return (is_type(c) || is_digit(c) || is_spec(c));
}
