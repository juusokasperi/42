/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 19:51:20 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 12:09:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flag_width(va_list *args, t_flags *flags)
{
	flags->star = 1;
	flags->width = va_arg(*args, int);
	if (flags->width < 0)
	{
		flags->left = 1;
		flags->width *= -1;
	}
}

static int	flag_precision(const char *format,
	int i, va_list *args, t_flags *flags)
{
	int	j;

	j = i;
	flags->zero = 0;
	if (format[j] == '*')
	{
		flags->prec = va_arg(*args, int);
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

int	store_flag_info(const char *format, t_flags *f, va_list *args, int j)
{
	if (format[j] == '-')
	{
		f->left = 1;
		f->zero = 0;
	}
	else if (format[j] == '0' && f->prec == -1 && !f->left && !f->width)
		f->zero = 1;
	else if (format[j] == '#')
		f->hash = 1;
	else if (format[j] == ' ' || format[j] == '+')
		f->positive = flag_positive(f->positive, format[j]);
	else if (format[j] == '*')
		flag_width(args, f);
	else if (format[j] == '.')
		j = flag_precision(format, j + 1, args, f);
	else if (ft_isdigit(format[j]))
		flag_digit(format[j], f);
	return (j);
}

int	parse_flags(const char *format, t_flags *f, va_list *args, int i)
{
	int	j;

	j = i;
	while (format[++j] && (is_flag(format[j])))
	{
		j = store_flag_info(format, f, args, j);
		if (ft_strchr("cspdiuxX%", format[j]))
		{
			f->specifier = format[j];
			break ;
		}
		if (!ft_strchr(ARGS, format[j]))
			break ;
	}
	if (!f->specifier)
	{
		init_flags(f);
		return (i);
	}
	return (j);
}
