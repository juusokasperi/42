/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:30:28 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/11 16:22:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	cmp(int ret, int ret_ft)
{
	if (ret == ret_ft)
		printf("%s✅ Return values match (%i)%s\n\n", KGRN, ret, KNRM);
	else
		printf("%s❌ Return values don't match: (PF: %i, FT: %i)%s\n\n", KRED, ret, ret_ft, KNRM);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || ft_strlen(argv[1]) != 1)
		return (ft_printf("Usage: ./test <i, d, u, s, c, p, x, X>\n"));
	if (argv[1][0] == 'i' || argv[1][0] == 'd')
		test_int();
	else if (argv[1][0] == 'u')
		test_unsigned();
	else if (argv[1][0] == 'x')
		test_lower_hex();
	else if (argv[1][0] == 'X')
		test_upper_hex();
	else if (argv[1][0] == 'p')
		test_ptr();
	else if (argv[1][0] == 's')
		test_str();
	else if (argv[1][0] == 'c')
		test_char();
	else if (argv[1][0] == 'e')
		test_eval();
	return (0);
}
