/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:06:48 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/15 09:46:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Width	toimii kaikilla
-		toimii kaikilla
0	Toimii kaikilla
+	Toimii vaan int
' '	Toimii vaan int
'-'	overrideaa 0:n (hoidettu parserissa)
'.'	int, unsigned, hex, (ptr).
	Minimum number of digits -> jos luku lyhempi, laitetaan
	nollia eteen
'#'	x ja X eteen tulee 0x tai 0X paitsi jos kyseessä luku 0

Tsekkaa print_ptr testi koulun koneella
*/

#include "ft_printf.h"

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
	else if (c == 'p')
		res = print_ptr_handler((unsigned long int)va_arg(*args, void *),
				flags);
	else if (c == 'i' || c == 'd')
		res = print_nbr_handler(va_arg(*args, int), flags);
	else if (c == 'u')
		res = print_unsigned_handler(va_arg(*args, unsigned int), flags);
	else if (c == 'x')
		res = print_hex_handler(va_arg(*args, unsigned int), 0, flags);
	else if (c == 'X')
		res = print_hex_handler(va_arg(*args, unsigned int), 1, flags);
	return (res);
}

static int	printf_logic(const char *format, int *i,
				bool *trailing_percent, va_list *args)
{
	t_flags	flags;
	int		res;

	res = 0;
	init_flags(&flags);
	if (format[*i] == '%' && format[*i + 1] && ft_strchr(ARGS, format[*i + 1]))
		*i = parse_flags(format, &flags, *args, *i);
	if (flags.specifier > 0 && ft_strchr("cspdiuxX%", format[*i]))
		res = type_handler(format[*i], args, flags);
	else if (format[*i] == '%' && !format[*i + 1] && !trailing_percent)
		return (-1);
	else if (format[*i])
	{
		if (format[*i] == '%')
			(*trailing_percent) = true;
		res = print_char(format[*i], flags);
	}
	if (res == -1)
		return (-1);
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
