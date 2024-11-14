/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 10:43:36 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(const char *str)
{
	return (write(1, str, ft_strlen(str)));
}

int	print_str_handler(const char *str)
{
	if (!str)
		str = "(null)";
	return (print_str(str));
}
