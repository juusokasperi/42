/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 12:07:52 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char c, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.left == 0)
		count += pad_width(flags.width, 1, 0);
	count += print_c(c);
	if (flags.left == 1)
		count += pad_width(flags.width, 1, 0);
	return (count);
}

int	print_c(char c)
{
	return (write (1, &c, 1));
}
