/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 09:46:09 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/15 09:51:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flags(t_flags *flags)
{
	flags->specifier = 0;
	flags->width = 0;
	flags->prec = -1;
	flags->zero = 0;
	flags->left = 0;
	flags->positive = 0;
	flags->hash = 0;
	flags->star = 0;
}

char	flag_positive(char positive, char c)
{
	if (c == ' ' && !positive)
		return (c);
	else if (c == '+')
		return (c);
	else
		return (positive);
}
