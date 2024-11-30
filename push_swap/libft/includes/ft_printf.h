/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:07:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/30 16:37:34 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdint.h>
# include <stdarg.h>
# include <stdbool.h>

int		ft_printf(const char *format, ...);
int		print_nbr_handler(int nbr);
int		print_hexptr_handler(uintptr_t n, bool capital, bool is_ptr);
int		print_unsigned_handler(unsigned int nbr);

#endif
