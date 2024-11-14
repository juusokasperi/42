/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:06:48 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 18:23:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_handler(char c, va_list *args)
{
	int	res;

	res = 0;
	if (c == '%')
		res = print_char('%');
	else if (c == 'c')
		res = print_char(va_arg(*args, int));
	else if (c == 's')
		res = print_str_handler(va_arg(*args, const char *));
	else if (c == 'p')
		res = print_ptr_handler((unsigned long int)va_arg(*args, void *));
	else if (c == 'i' || c == 'd')
		res = print_nbr_handler(va_arg(*args, int));
	else if (c == 'u')
		res = print_unsigned_handler(va_arg(*args, unsigned int));
	else if (c == 'x')
		res = print_hex_handler(va_arg(*args, unsigned int), 0);
	else if (c == 'X')
		res = print_hex_handler(va_arg(*args, unsigned int), 1);
	return (res);
}

int	printf_handler(const char *format, va_list *args)
{
	int		i;
	int		count;
	int		res;

	i = 0;
	res = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]))
		{
			res = type_handler(format[i + 1], args);
			i++;
		}
		else
			res = print_char(format[i]);
		if (res == -1)
			return (-1);
		i++;
		count += res;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format || !(*format))
		return (0);
	va_start(args, format);
	count = printf_handler(format, &args);
	va_end(args);
	return (count);
}
