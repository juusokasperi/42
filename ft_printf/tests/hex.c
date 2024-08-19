/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/19 16:12:27 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

void	test_hex(void)
{
	printf("--------------------\n- TESTING HEX -\n--------------------\n");
//	printf("PF: %x\n", -2147483648);
//	ft_printf("FT: %x\n", -2147483648);
	printf("PF: %x\n", 2147483647);
	ft_printf("FT: %x\n\n", 2147483647);
	printf("PF: %x\n", 0);
	ft_printf("FT: %x\n\n", 0);

	printf("Test 0 with various flags\n");
	printf("PF: %.0x\n", 0);
	ft_printf("FT: %.0x\n", 0);
	printf("PF: %#x\n", 0);
	ft_printf("FT: %#x\n", 0);
	printf("PF: %x\n", 0);
	ft_printf("FT: %x\n", 0);
	printf("PF: %0x\n", 0);
	ft_printf("FT: %0x\n", 0);
	printf("PF: %.5x\n", 0);
    ft_printf("FT: %.5x\n\n", 0);

	printf("Precision 0 with non-zero numbers\n");
	printf("PF: %.0X\n", 42);
    ft_printf("FT: %.0X\n", 42);
    printf("PF: %.0X\n", -42);
    ft_printf("FT: %.0X\n\n", -42);

	printf("Width flag:\n");
	printf("PF: %10x\n", -10);
	ft_printf("FT: %10x\n", -10);
	printf("PF: %10x\n", 10);
	ft_printf("FT: %10x\n", 10);
	printf("PF: %#10x\n", 10);
	ft_printf("FT: %#10x\n\n", 10);

	printf("Width flag with 0 padding\n");
	printf("PF: %010x\n", -10);
	ft_printf("FT: %010x\n", -10);
	printf("PF: %010x\n", 10);
	ft_printf("FT: %010x\n", 10);
	printf("PF: %0#10x\n", 10);
	ft_printf("FT: %0#10x\n", 10);
	printf("PF: %010X\n", 10);
	ft_printf("FT: %010X\n", 10);
	printf("PF: %#010X\n", 2147483647);
	ft_printf("FT: %#010X\n\n", 2147483647);

	printf("Left-align\n");
	printf("PF: %-10Xx\n", -10);
	ft_printf("FT: %-10Xx\n", -10);
	printf("PF: %-10xx\n", 10);
	ft_printf("FT: %-10xx\n", 10);
	printf("PF: %-#10Xx\n", 10);
	ft_printf("FT: %-#10Xx\n", 10);
	printf("PF: %-#10xx\n", 10);
	ft_printf("FT: %-#10xx\n\n", 10);

	printf("Precision\n");
	printf("PF: %.0x\n", 15454);
	ft_printf("FT: %.0x\n", 15454);
	printf("PF: %.0x\n", -15454);
	ft_printf("FT: %.0x\n", -15454);
	printf("PF: %.10x\n", 15454);
	ft_printf("FT: %.10x\n", 15454);
	printf("PF: %.10x\n", -15454);
	ft_printf("FT: %.10x\n", -15454);
	printf("PF: %20.10X\n", -15454);
	ft_printf("FT: %20.10X\n", -15454);
	printf("PF: %-20.10xx\n", -15454);
	ft_printf("FT: %-20.10xx\n", -15454);
	printf("PF: %.2x\n", 123);
	ft_printf("FT: %.2x\n", 123);
	printf("PF: %#010.5X\n", 123);
    ft_printf("FT: %#010.5X\n\n", 123);

	printf("Combining width, precision, flags\n");
	printf("PF: %#08.5x\n", 123);
	ft_printf("FT: %#08.5x\n", 123);
	printf("PF: %#10.5X\n", -123);
	ft_printf("FT: %#10.5X\n\n", -123);

	printf("Large width and precision:\n");
	printf("PF: %50.30X\n", 123456);
	ft_printf("FT: %50.30X\n\n", 123456);

	printf("Negative width:\n");
	printf("PF: %-10x\n", 42);
	ft_printf("FT: %-10x\n\n", 42);

	printf("Multiple flags:\n");
	printf("PF: %#-10.5x\n", 123);
	ft_printf("FT: %#-10.5x\n", 123);
	printf("PF: %0#10.5X\n", 123);
	ft_printf("FT: %0#10.5X\n\n", 123);
	printf("--------------------\n-  HEX  TEST  ENDS -\n--------------------\n");
}
