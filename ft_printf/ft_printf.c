/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:06:48 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/07 20:48:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_handler(char c, va_list *args, int *i)
{
	int	count;

	count = 0;
	if (c == '%')
		count += print_char('%');
	else if (c == 'c')
		count += print_char(va_arg(*args, int));
	else if (c == 's')
		count += print_str(va_arg(*args, const char *));
	else if (c == 'p')
		count += print_ptr((unsigned long int)va_arg(*args, void *));
	else if (c == 'i' || c == 'd')
		count += print_nbr(va_arg(*args, int));
	else if (c == 'u')
		count += print_unsigned(va_arg(*args, unsigned int));
	else if (c == 'x')
		count += print_hex(va_arg(*args, unsigned int), 0);
	else if (c == 'X')
		count += print_hex(va_arg(*args, unsigned int), 1);
	(*i)++;
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!format || !(*format))
		return (0);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			count += type_handler(format[i + 1], &args, &i);
		else if (format[i] == '%' && !(format[i + 1]))
			return (count);
		else
			count += print_char(format[i]);
		i++;
	}
	return (count);
}

int	main(void)
{
	int	i;
	int	j;
	int	ptr;

	ptr = 5;
	i = ft_printf("%c %s %p %i %d %u %x %X\n", 'a', "string", &ptr, 15454, 15454, 15454, 15454, 15454);
	j = printf("%c %s %p %i %d %u %x %X\n", 'a', "string", &ptr, 15454, 15454, 15454, 15454, 15454);
	printf("ft_printf returns %i and printf returns %i\n", i, j);
	return (0);
}
