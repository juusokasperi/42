/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:06:48 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/25 12:05:05 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	type_handler(char c, va_list *args)
{
	const char	*str;

	if (c == '%')
		return (ft_putchar_fd('%', 1));
	else if (c == 'c')
		return (ft_putchar_fd(va_arg(*args, int), 1));
	else if (c == 's')
	{
		str = va_arg(*args, const char *);
		if (!str)
			str = "(null)";
		return (ft_putstr_fd((char *)str, 1));
	}
	else if (c == 'p')
		return (print_hexptr_handler(
				(unsigned long int)va_arg(*args, void *), 0, 1));
	else if (c == 'i' || c == 'd')
		return (print_nbr_handler(va_arg(*args, int)));
	else if (c == 'u')
		return (print_unsigned_handler(va_arg(*args, unsigned int)));
	else if (c == 'x')
		return (print_hexptr_handler(va_arg(*args, unsigned int), 0, 0));
	else if (c == 'X')
		return (print_hexptr_handler(va_arg(*args, unsigned int), 1, 0));
	return (0);
}

static int	handle_regular_print(char c, bool *trailing_percent)
{
	if (c == '%')
		(*trailing_percent) = true;
	return (ft_putchar_fd(c, 1));
}

static int	printf_handler(const char *format, va_list *args)
{
	int		i;
	int		count;
	int		res;
	bool	trailing_percent;

	i = 0;
	trailing_percent = false;
	count = 0;
	while (format[i])
	{
		res = 0;
		if (format[i] == '%' && format[i + 1]
			&& ft_strchr("cspdiuxX%", format[i + 1]))
			res = type_handler(format[++i], args);
		else if (format[i] == '%' && !format[i + 1] && !trailing_percent)
			return (-1);
		else
			res = handle_regular_print(format[i], &trailing_percent);
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

	if (!format)
		return (-1);
	va_start(args, format);
	count = printf_handler(format, &args);
	va_end(args);
	return (count);
}
