/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_putnbrfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:57:21 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 18:08:11 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_putnbrfd(void)
{
	printf("---------------------------\n");
	printf("FT_PUTNBRFD:\n");
	printf("Int '-2147483648' to stdout:\n");
	ft_putnbr_fd(-2147483648, 1);
	printf("\n\nInt '-2147483640' to stdout:\n");
	ft_putnbr_fd(-2147483640, 1);
	printf("\n\nInt '3003003000' to stdout:\n");
	ft_putnbr_fd(3003003000, 1);
	printf("\n\nInt '2147483647' to stdout:\n");
	ft_putnbr_fd(2147483647, 1);
	printf("\n\nInt '0' to stdout:\n");
	ft_putnbr_fd(0, 1);
	printf("\n\nInt '5' to stdout:\n");
	ft_putnbr_fd(5, 1);
	printf("\n\nInt '-5' to stdout:\n");
	ft_putnbr_fd(-5, 1);
	printf("\n\nChar 'A' (65) to stdout:\n");
	ft_putnbr_fd('A', 1);
	printf("\n\nChar 'A' (65) to stdin:\n");
	ft_putnbr_fd('A', 0);
	printf("\n\nChar 'A' (65) to stderror:\n");
	ft_putnbr_fd('A', 2);
	printf("\n---------------------------\n\n");
}
