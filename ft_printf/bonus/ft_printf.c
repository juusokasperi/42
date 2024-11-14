/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:06:48 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 15:50:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flags(t_flags *flags)
{
	flags->specifier = 0;
	flags->width = 0;
	flags->prec = -1;
	flags->zero = 0;
	flags->left = 0;
	flags->positive = 0;
	flags->hash = 0;
	flags->star = 0;
	flags->negative = 0;
}

int	type_handler(char c, va_list *args, t_flags flags)
{
	int	res;

	res = 0;
	if (c == '%')
		res = print_c('%');
	else if (c == 'c')
		res = print_char(va_arg(*args, int), flags);
	else if (c == 's')
		res = print_str_handler(va_arg(*args, const char *), flags);
//	else if (c == 'p')
//		res = print_ptr_handler((unsigned long int)va_arg(*args, void *),
//				flags);
//	else if (c == 'i' || c == 'd')
//		res = print_nbr_handler(va_arg(*args, int), &flags);
//	else if (c == 'u')
//		res = print_unsigned_handler(va_arg(*args, unsigned int), flags);
//	else if (c == 'x')
//		res = print_hex_handler(va_arg(*args, unsigned int), 0, &flags);
//	else if (c == 'X')
//		res = print_hex_handler(va_arg(*args, unsigned int), 1, &flags);
	return (res);
}

int	printf_handler(const char *format, va_list *args)
{
	t_flags	flags;
	int		i;
	int		count;
	int		res;

	i = 0;
	count = 0;
	res = 0;
	while (format[i])
	{
		init_flags(&flags);
		if (format[i] == '%' && format[i + 1])
			i = parse_flags(format, &flags, *args, i);
		if (flags.specifier > 0 && ft_strchr("cspdiuxX%", format[i]))
			res = type_handler(format[i], args, flags);
		else
			res = print_c(format[i]);
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
