/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:44:26 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/12 16:20:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	test_ptr(void)
{
	int i = 500;
	void	*p = NULL;
	printf("--------------------\n- TESTING PTR -\n--------------------\n");
	printf("PF: %p\n", &i);
	ft_printf("FT: %p\n", &i);
	printf("PF: %p\n", p);
	ft_printf("FT: %p\n\n", p);

//	printf("Test 0 with various flags\n");
//	printf("PF: %.0p\n", 0);
//	ft_printf("FT: %.0p\n", 0);
//	printf("PF: %#p\n", 0);
//	ft_printf("FT: %#p\n", 0);
//	printf("PF: %0p\n", p);
//	ft_printf("FT: %0p\n", p);
//	printf("PF: %.5p\n", p);
//	ft_printf("FT: %.5p\n\n", p);

//	printf("Precision 0 with non-zero numbers\n");
//	printf("PF: %.0p\n", &i);
//	ft_printf("FT: %.0p\n", &i);
//	printf("PF: %.0p\n", &i);
//	ft_printf("FT: %.0p\n\n", &i);

	printf("Width flag:\n");
	printf("PF: %10p\n", &i);
	ft_printf("FT: %10p\n", &i);
	printf("PF: %10p\n", &i);
	ft_printf("FT: %10p\n\n", &i);
//	printf("PF: %#10p\n", &i);
//	ft_printf("FT: %#10p\n\n", &i);

//	printf("Width flag with 0 padding\n");
//	printf("PF: %010p\n", &i);
//	ft_printf("FT: %010p\n", &i);
//	printf("PF: %010p\n", &i);
//	ft_printf("FT: %010p\n", &i);
//	printf("PF: %0#10p\n", &i);
//	ft_printf("FT: %0#10p\n", &i);
//	printf("PF: %010p\n", &i);
//	ft_printf("FT: %010p\n", &i);
//	printf("PF: %#010p\n", &i);
//	ft_printf("FT: %#010p\n\n", &i);

	printf("Left-align\n");
	printf("PF: %-10px\n", &i);
	ft_printf("FT: %-10px\n", &i);
	printf("PF: %-10px\n", &i);
	ft_printf("FT: %-10px\n\n", &i);
//	printf("PF: %-#10px\n", &i);
//	ft_printf("FT: %-#10px\n", &i);
//	printf("PF: %-#10px\n", &i);
//	ft_printf("FT: %-#10px\n\n", &i);

//	printf("Precision\n");
//	printf("PF: %.0p\n", &i);
//	ft_printf("FT: %.0p\n", &i);
//	printf("PF: %.0p\n", &i);
//	ft_printf("FT: %.0p\n", &i);
//	printf("PF: %.10p\n", &i);
//	ft_printf("FT: %.10p\n", &i);
//	printf("PF: %.10p\n", &i);
//	ft_printf("FT: %.10p\n", &i);
//	printf("PF: %20.10p\n", &i);
//	ft_printf("FT: %20.10p\n", &i);
//	printf("PF: %-20.10px\n", &i);
//	ft_printf("FT: %-20.10px\n", &i);
//	printf("PF: %.2p\n", &i);
//	ft_printf("FT: %.2p\n", &i);
//	printf("PF: %#010.5p\n", &i);
//	ft_printf("FT: %#010.5p\n\n", &i);

//	printf("Combining width, precision, flags\n");
//	printf("PF: %#08.5p\n", &i);
//	ft_printf("FT: %#08.5p\n", &i);
//	printf("PF: %#10.5p\n", &i);
//	ft_printf("FT: %#10.5p\n\n", &i);

//	printf("Large width and precision:\n");
//	printf("PF: %50.30p\n", &i);
//	ft_printf("FT: %50.30p\n\n", &i);

	printf("Negative width:\n");
	printf("PF: %-10p\n", &i);
	ft_printf("FT: %-10p\n\n", &i);

//	printf("Multiple flags:\n");
//	printf("PF: %#-10.5p\n", &i);
//	ft_printf("FT: %#-10.5p\n", &i);
//	printf("PF: %0#10.5p\n", &i);
//	ft_printf("FT: %0#10.5p\n\n", &i);
//	printf("PF: %#p\n", &i);
//	ft_printf("FT: %#p\n", &i);
	printf("--------------------\n-  PTR  TEST  ENDS -\n--------------------\n");
}
