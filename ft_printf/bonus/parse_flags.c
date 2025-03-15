/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:51:20 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/15 09:46:32 by jrinta-          ###   ########.fr       */
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
		if (flags->prec < 0)
			flags->prec = 0;
		return (i++);
	}
	flags->prec = 0;
	if (!ft_isdigit(format[i]))
		return (i++);
	while (ft_isdigit(format[i]))
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
	while (format[++i] && (is_flag(format[i])))
	{
		if (format[i] == '-')
			flag_left(f);
		else if (format[i] == '0' && f->prec == -1 && !f->left && !f->width)
			f->zero = 1;
		else if (format[i] == '#')
			f->hash = 1;
		else if (format[i] == ' ' || format[i] == '+')
			f->positive = flag_positive(f->positive, format[i]);
		else if (format[i] == '*')
			flag_width(args, f);
		else if (format[i] == '.')
			i = flag_precision(format, i + 1, args, f);
		else if (ft_isdigit(format[i]))
			flag_digit(format[i], f);
		else if (ft_strchr("cspdiuxX%", format[i]))
		{
			f->specifier = format[i];
			break ;
		}
		if (!ft_strchr(ARGS, format[i]))
			break ;
	}
	return (i);
}
