/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:33:28 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/11 14:28:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "colors.h"
# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <limits.h>

void	test_int(void);
void	test_unsigned(void);
void	test_hex(void);
void	test_ptr(void);
void	test_str(void);
void	test_char(void);
void	test_false(void);
void	test_eval(void);
void	cmp(int ret, int ret_ft);

#endif
