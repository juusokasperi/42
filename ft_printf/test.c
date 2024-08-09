/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:30:28 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/09 22:04:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	test_int(void)
{
	printf("--------------------\n- TESTING INTEGERS -\n--------------------\n");
	printf("First printing int 0 with precision 0 (should be empty):\n");
	printf("PF: %.0i\n", 0);
	ft_printf("FT: %.0i\n---\n", 0);

	printf("Printing just ints with no flags\n");
	printf("PF: %i\n", 0);
	ft_printf("FT: %i\n", 0);
	printf("PF: %i\n", -2147483647);
	ft_printf("FT: %i\n", -2147483647);
	printf("PF: %i\n", 2147483647);
	ft_printf("FT: %i\n---\n", 2147483647);

	printf("Width flag:\n");
	printf("PF: %10i\n", -10);
	ft_printf("FT: %10i\n", -10);
	printf("PF: %10i\n", 10);
	ft_printf("FT: %10i\n", 10);
	printf("PF: %+10i\n", 10);
	ft_printf("FT: %+10i\n---\n", 10);

	printf("Width flag with 0 padding:\n");
	printf("PF: %010i\n", -10);
	ft_printf("FT: %010i\n", -10);
	printf("PF: %0 10i\n", 10);
	ft_printf("FT: %0 10i\n", 10);
	printf("PF: %0+10i\n", 10);
	ft_printf("FT: %0+10i\n", 10);
	printf("PF: %010i\n", 10);
	ft_printf("FT: %010i\n", 10);
	printf("PF: %010i\n", 2147483647);
	ft_printf("FT: %010i\n---\n", 2147483647);

	printf("Left-align:\n");
	printf("PF: %-10ix\n", -10);
	ft_printf("FT: %-10ix\n", -10);
	printf("PF: %-10ix\n", 10);
	ft_printf("FT: %-10ix\n", 10);
	printf("PF: %- 10ix\n", 10);
	ft_printf("FT: %- 10ix\n", 10);
	printf("PF: %-+10ix\n", 10);
	ft_printf("FT: %-+10ix\n---\n", 10);

	printf("Precision:\n");
	printf("PF: %.10i\n", 15454);
	ft_printf("FT: %.10i\n", 15454);
	printf("PF: %.10i\n", -15454);
	ft_printf("FT: %.10i\n", -15454);
	printf("PF: %20.10i\n", -15454);
	ft_printf("FT: %20.10i\n", -15454);
	printf("PF: %-20.10ix\n", -15454);
	ft_printf("FT: %-20.10ix\n", -15454);
	printf("--------------------\n");
}
int	main(void)
{
	test_int();
	return (0);
}
