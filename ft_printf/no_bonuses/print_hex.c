/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:23:34 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 11:16:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_handler(unsigned int nbr, int capital)
{
	int		res;
	char	*hex_xtoa;

	res = 0;
	hex_xtoa = ft_xtoa(nbr, capital, 0);
	if (!hex_xtoa)
		return (-1);
	res = print_str(hex_xtoa);
	free(hex_xtoa);
	return (res);
}
