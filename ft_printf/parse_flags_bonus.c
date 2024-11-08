/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:51:20 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/31 20:25:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flag_left(t_flags *flags)
{
	flags->left_align = 1;
	flags->zero_pad = 0;
}

static void	flag_width(va_list args, t_flags *flags)
{
	flags->star = 1;
	flags->width = va_arg(args, int);
	if (flags->width < 0)
	{
		flags->left_align = 1;
		flags->width *= -1;
	}
}

static int	flag_precision(const char *format,
	int i, va_list args, t_flags *flags)
{
	int	j;

	j = i;
	flags->zero_pad = 0;
	if (format[j] == '*')
	{
		flags->precision = va_arg(args, int);
		return (i++);
	}
	flags->precision = 0;
	while (is_digit(format[i]))
	{
		flags->precision = (flags->precision * 10) + (format[i] - '0');
		i++;
	}
	return (i);
}

static void	flag_digit(char c, t_flags *flags)
{
	if (flags->star == 1)
		flags->width = 0;
	flags->width = (flags->width * 10) + (c - '0');
}

void	parse_flags(const char *format, t_flags *flags, va_list args, int *i)
{
	while (format[++(*i)] && is_flag(format[*i]))
	{
		if (format[*i] == '-')
			flag_left(flags);
		if (format[*i] == '0' && flags->precision == -1
			&& flags->left_align == 0 && flags->width == 0)
			flags->zero_pad = 1;
		if (format[*i] == '#')
			flags->hash = 2;
		if (format[*i] == ' ' && !flags->positive_sign)
			flags->positive_sign = ' ';
		if (format[*i] == '+')
			flags->positive_sign = '+';
		if (format[*i] == '*')
			flag_width(args, flags);
		if (format[*i] == '.')
			*i = flag_precision(format, (*i) + 1, args, flags);
		if (is_digit(format[*i]))
			flag_digit(format[*i], flags);
		if (is_type(format[*i]))
		{
			flags->specifier = format[*i];
			break ;
		}
	}
}
