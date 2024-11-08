/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_putcharfd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:57:21 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 12:12:19 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_putcharfd(void)
{
	printf("---------------------------\n");
	printf("FT_PUTCHARFD:\n");
	printf("Int '65' to stdout:\n");
	ft_putchar_fd(65, 1);
	printf("\n\nChar 'Y' to stdout:\n");
	ft_putchar_fd('Y', 1);
	printf("\n\nInt 'INT_MAX' to stdout:\n");
	ft_putchar_fd((char)INT_MAX, 1);
	printf("\n\nInt 'INT_MIN' to stdout:\n");
	ft_putchar_fd((char)INT_MIN, 1);
	printf("\n\nInt '0' to stdout:\n");
	ft_putchar_fd(0, 1);
	printf("\n\nChar '@' to stdout:\n");
	ft_putchar_fd('@', 1);
	printf("\n\nChar '#' to stdout:\n");
	ft_putchar_fd('#', 1);
	printf("\n\nChar '\t' to stdout:\n");
	ft_putchar_fd('\t', 1);
	printf("\n\nChar 'A' (65) to stdin:\n");
	ft_putchar_fd('A', 0);
	printf("\n\nChar 'A' (65) to stderror:\n");
	ft_putchar_fd('A', 2);
	printf("\n---------------------------\n\n");
}
