/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:24:51 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 19:38:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_ptr_handler(unsigned long int nbr)
{
	int		count;
	char	*ptr_xtoa;

	count = 0;
	count += print_s("0x");
	ptr_xtoa = ft_xtoa(nbr, 0);
	if (!ptr_xtoa)
		return (0);
	count += print_s(ptr_xtoa);
	free(ptr_xtoa);
	return (count);
}
