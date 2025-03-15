/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:33:28 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/22 16:37:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "colors.h"
# include "ft_printf.h"
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>

void	test_int(void);
void	test_unsigned(void);
void	test_upper_hex(void);
void	test_lower_hex(void);
void	test_ptr(void);
void	test_str(void);
void	test_char(void);
void	test_others(void);
void	test_eval(void);
void	cmp(int ret, int ret_ft);

#endif
