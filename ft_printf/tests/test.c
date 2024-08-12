/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:30:28 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/12 20:23:17 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	test_int(void);
void	test_unsigned(void);
void	test_hex(void);
void	test_ptr(void);
void	test_str(void);
void	test_char(void);
void	test_false(void);

int	main(int argc, char **argv)
{
	int	i;

	i = 50;
	if (argc != 2 || ft_strlen(argv[1]) != 1)
		return (ft_printf("Usage: ./test <i, d, u, s, c, p, x, X>\n"));
	if (argv[1][0] == 'i' || argv[1][0] == 'd')
		test_int();
	else if (argv[1][0] == 'u')
		test_unsigned();
	else if (argv[1][0] == 'x' || argv[1][0] == 'X')
		test_hex();
	else if (argv[1][0] == 'p')
		test_ptr();
	else if (argv[1][0] == 's')
		test_str();
	else if (argv[1][0] == 'c')
		test_char();
	ft_printf("\n\n");
	ft_printf("%15i | %15d | %15s | %15c\n", 10, 10, "test", 'c');
	ft_printf("%15x | %15X | %15p | %15u\n", 15454, 15454, &i, 10);
	return (0);
}
