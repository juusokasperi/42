/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:06:48 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 19:47:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_handler(char c, va_list *args)
{
	int	count;

	count = 0;
	if (c == '%')
		count += print_c('%');
	else if (c == 'c')
		count += print_c(va_arg(*args, int));
	else if (c == 's')
		count += print_str_handler(va_arg(*args, const char *));
	else if (c == 'p')
		count += print_ptr_handler((unsigned long int)va_arg(*args, void *));
	else if (c == 'i' || c == 'd')
		count += print_nbr_handler(va_arg(*args, int));
	else if (c == 'u')
		count += print_unsigned_handler(va_arg(*args, unsigned int));
	else if (c == 'x')
		count += print_hex_handler(va_arg(*args, unsigned int), 0);
	else if (c == 'X')
		count += print_hex_handler(va_arg(*args, unsigned int), 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;
	char	specifier;

	i = 0;
	count = 0;
	if (!format || !(*format))
		return (0);
	va_start(args, format);
	while (format[i])
	{
		specifier = 0;
		if (format[i] == '%' && format[i + 1])
			specifier = format[++i];
		if (specifier && is_type(format[i]))
			count += type_handler(format[i], &args);
		else if (format[i] == '%' && !(format[i + 1]))
			return (count);
		else
			count += print_c(format[i]);
		i++;
	}
	return (count);
}
