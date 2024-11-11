/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:23:34 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 19:35:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex_handler(unsigned int nbr, int capital)
{
	int		count;
	char	*hex_xtoa;

	count = 0;
	hex_xtoa = ft_xtoa(nbr, capital);
	if (!hex_xtoa)
		return (0);
	count += print_s(hex_xtoa);
	free(hex_xtoa);
	return (count);
}
