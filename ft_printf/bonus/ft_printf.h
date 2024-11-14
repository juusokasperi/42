/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:07:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/14 10:14:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_flags
{
	char	specifier;
	int		width;
	int		prec;
	int		zero;
	int		left;
	char	positive;
	int		hash;
	int		star;
	int		negative;
}		t_flags;

int		parse_flags(const char *format, t_flags *f, va_list args, int i);
int		pad_width(int width, int size, int zero_pad);
int		print_c(char c);
int		is_type(char c);
int		is_digit(char c);
int		is_spec(char c);
int		is_flag(char c);
int		print_hex_handler(unsigned int nbr, int capital, t_flags *flags);
int		print_char(char c, t_flags flags);
int		print_ptr_handler(uintptr_t n, t_flags flags);
int		print_unsigned_handler(unsigned int nbr, t_flags flags);
int		print_nbr_handler(int nbr, t_flags *flags);
int		print_str_handler(const char *str, t_flags flags);
int		print_s(const char *str);
int		ft_printf(const char *, ...);
char	*ft_ltoa(long n);
char	*ft_xtoa(uintptr_t n, int capital);

#endif
