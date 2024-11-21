/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:24:51 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/16 17:28:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_ptr_handler(uintptr_t nbr)
{
	int		res;
	char	*ptr_xtoa;

	res = 0;
	if (!nbr)
		return (print_str("(nil)"));
	ptr_xtoa = ft_xtoa(nbr, 0, 1);
	if (!ptr_xtoa)
		return (-1);
	res = print_str(ptr_xtoa);
	free(ptr_xtoa);
	return (res);
}
