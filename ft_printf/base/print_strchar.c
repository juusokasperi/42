/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 19:49:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(char c)
{
	write (1, &c, 1);
	return (1);
}

int	print_s(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i += print_c(str[i]);
	return (i);
}

int	print_str_handler(const char *str)
{
	int	count;

	count = 0;
	if (!str)
		str = "(null)";
	count += print_s(str);
	return (count);
}
