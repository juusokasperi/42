/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:07:43 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 12:09:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# define ARGS "cspdiuxX%-.# +0123456789*"

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
}		t_flags;

int		parse_flags(const char *format, t_flags *f, va_list *args, int i);
char	flag_positive(char positive, char c);
void	init_flags(t_flags *flags);

char	*pad_width(int width, int size, int zero_pad);
int		is_flag(char c);
int		print_char(int c, t_flags flags);
int		print_hex_handler(unsigned int nbr, int capital, t_flags flags);
int		print_ptr_handler(uintptr_t n, t_flags flags);
int		print_unsigned_handler(unsigned int nbr, t_flags flags);
int		print_nbr_handler(int nbr, t_flags flags);
int		print_str_handler(const char *str, t_flags flags);
int		ft_printf(const char *, ...);
char	*ft_ltoa(long n);
char	*ft_xtoa(uintptr_t n, int capital);
int		print_and_free(char *str);
int		has_only_zeros(char *str);
char	*append_padding_nbr(char *nbr_itoa, t_flags flags);

#endif
