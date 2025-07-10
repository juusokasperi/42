/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:59:10 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 10:49:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_eval(void)
{
	int	i = 50;
	int	a;
	int	b;
	char *ptr = NULL;
	ft_printf("%s------------------------------\nMandatory tests\n\n%s",
		KYEL, KNRM);
	a = ft_printf("%i | %d | %s | %c\n", 10, 10, "test", 'c');
	b = printf("%i | %d | %s | %c\n", 10, 10, "test", 'c');
	cmp(a, b);
	a = ft_printf("%x | %X | %p | %u\n", 15454, 15454, &i, 10);
	b = printf("%x | %X | %p | %u\n", 15454, 15454, &i, 10);
	cmp(a, b);
	a = ft_printf("%s\n", "");
	b = printf("%s\n", "");
	cmp(a, b);
	a = ft_printf("%i\n", -2147483648);
	b = printf("%li\n", -2147483648);
	cmp(a, b);
	a = ft_printf("%d\n", 0);
	b = printf("%d\n", 0);
	cmp(a, b);
	a = ft_printf("cspd%iouxX\n", 50);
	b = printf("cspd%iouxX\n", 50);
	cmp(a, b);
	ft_printf("%i%i%i%i%i%i%i%ix\n", 1, 1, 1, 1, 1, 1, 1, 1);
	a = ft_printf("cs%pdiouxX\n", ptr);
	b = printf("cs%pdiouxX\n", ptr);
	cmp(a, b);
}
