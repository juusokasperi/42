/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:06:48 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 12:08:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_handler(char c, va_list *args, t_flags flags)
{
	if (c == '%')
		return (ft_putchar_fd('%', 1));
	else if (c == 'c')
		return (print_char(va_arg(*args, int), flags));
	else if (c == 's')
		return (print_str_handler(va_arg(*args, const char *), flags));
	else if (c == 'p')
		return (print_ptr_handler((unsigned long int)va_arg(*args, void *),
				flags));
	else if (c == 'i' || c == 'd')
		return (print_nbr_handler(va_arg(*args, int), flags));
	else if (c == 'u')
		return (print_unsigned_handler(va_arg(*args, unsigned int), flags));
	else if (c == 'x')
		return (print_hex_handler(va_arg(*args, unsigned int), 0, flags));
	else if (c == 'X')
		return (print_hex_handler(va_arg(*args, unsigned int), 1, flags));
	return (0);
}

static int	printf_logic(const char *format, int *i,
				bool *trailing_percent, va_list *args)
{
	t_flags	flags;
	int		res;

	res = 0;
	init_flags(&flags);
	if (format[*i] == '%' && format[*i + 1] && ft_strchr(ARGS, format[*i + 1]))
		*i = parse_flags(format, &flags, args, *i);
	if (flags.specifier > 0 && ft_strchr("cspdiuxX%", format[*i]))
		res = type_handler(format[*i], args, flags);
	else if (format[*i] == '%' && !format[*i + 1] && !(*trailing_percent))
		return (-1);
	else if (format[*i])
	{
		if (format[*i] == '%')
			(*trailing_percent) = true;
		res = print_char(format[*i], flags);
	}
	return (res);
}

int	printf_handler(const char *format, va_list *args)
{
	int		i;
	int		count;
	int		res;
	bool	trailing_percent;

	i = 0;
	count = 0;
	trailing_percent = false;
	while (format[i])
	{
		res = printf_logic(format, &i, &trailing_percent, args);
		if (res == -1)
			return (-1);
		if (format[i])
			i++;
		count += res;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = printf_handler(format, &args);
	va_end(args);
	return (count);
}
