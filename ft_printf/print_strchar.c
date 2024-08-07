/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:26:53 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/07 20:27:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	print_str(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count += print_char(str[i++]);
	}
	return (count);
}
