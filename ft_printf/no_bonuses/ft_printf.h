/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:07:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 18:46:41 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		print_hex_handler(unsigned int nbr, int capital);
int		print_char(char c);
int		print_ptr_handler(uintptr_t n);
int		print_unsigned_handler(unsigned int nbr);
int		print_nbr_handler(int nbr);
int		print_str_handler(const char *str);
int		print_str(const char *str);
int		ft_printf(const char *format, ...);
char	*ft_ltoa(long n);
char	*ft_xtoa(uintptr_t n, int capital, int is_ptr);

#endif
