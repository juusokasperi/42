/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:06:48 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/11 16:25:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flags(t_flags *flags)
{
	flags->specifier = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->zero_pad = 0;
	flags->left_align = 0;
	flags->positive_sign = 0;
	flags->hash = 0;
	flags->star = 0;
	flags->negative = 0;
}

int	type_handler(char c, va_list *args, t_flags flags)
{
	int	count;

	count = 0;
	if (c == '%')
		count += print_char('%', flags);
	else if (c == 'c')
		count += print_char(va_arg(*args, int), flags);
	else if (c == 's')
		count += print_str_handler(va_arg(*args, const char *), flags);
	else if (c == 'p')
		count += print_ptr_handler((unsigned long int)va_arg(*args, void *),
				flags);
	else if (c == 'i' || c == 'd')
		count += print_nbr_handler(va_arg(*args, int), &flags);
	else if (c == 'u')
		count += print_unsigned_handler(va_arg(*args, unsigned int), flags);
	else if (c == 'x')
		count += print_hex_handler(va_arg(*args, unsigned int), 0, &flags);
	else if (c == 'X')
		count += print_hex_handler(va_arg(*args, unsigned int), 1, &flags);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!format || !(*format))
		return (0);
	va_start(args, format);
	while (format[i])
	{
		init_flags(&flags);
		if (format[i] == '%' && format[i + 1])
			parse_flags(format, &flags, args, &i);
		if (flags.specifier > 0 && is_type(format[i]))
			count += type_handler(format[i], &args, flags);
		else if (format[i] == '%' && !(format[i + 1]))
			return (count);
		else
			count += print_c(format[i]);
		i++;
	}
	return (count);
}
