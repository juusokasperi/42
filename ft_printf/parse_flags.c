/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:51:20 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 00:35:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flag_left(t_flags *flags)
{
	flags->left = 1;
	flags->zero = 0;
}

static void	flag_width(va_list args, t_flags *flags)
{
	flags->star = 1;
	flags->width = va_arg(args, int);
	if (flags->width < 0)
	{
		flags->left = 1;
		flags->width *= -1;
	}
}

static int	flag_precision(const char *format,
	int i, va_list args, t_flags *flags)
{
	int	j;

	j = i;
	flags->zero = 0;
	if (format[j] == '*')
	{
		flags->prec = va_arg(args, int);
		return (i++);
	}
	flags->prec = 0;
	while (is_digit(format[i]))
	{
		flags->prec = (flags->prec * 10) + (format[i] - '0');
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

int	parse_flags(const char *format, t_flags *f, va_list args, int i)
{
	while (format[++i] && is_flag(format[i]))
	{
		if (format[i] == '-')
			flag_left(f);
		if (format[i] == '0' && f->prec == -1 && !f->left && !f->width)
			f->zero = 1;
		if (format[i] == '#')
			f->hash = 2;
		if (format[i] == ' ' && !f->positive)
			f->positive = ' ';
		if (format[i] == '+')
			f->positive = '+';
		if (format[i] == '*')
			flag_width(args, f);
		if (format[i] == '.')
			i = flag_precision(format, i + 1, args, f);
		if (is_digit(format[i]))
			flag_digit(format[i], f);
		if (is_type(format[i]))
		{
			f->specifier = format[i];
			break ;
		}
	}
	return (i);
}
