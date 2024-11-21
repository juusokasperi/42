/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:07:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/21 09:48:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdbool.h>

char	*ft_ltoa(long n);
int		ft_printf(const char *format, ...);
char	*ft_xtoa(uintptr_t n, int capital, int is_ptr);
int		print_char(char c);
int		print_hex_handler(unsigned int nbr, int capital);
int		print_nbr_handler(int nbr);
int		print_ptr_handler(uintptr_t n);
int		print_unsigned_handler(unsigned int nbr);
int		print_str_handler(const char *str);
int		print_str(const char *str);

#endif
