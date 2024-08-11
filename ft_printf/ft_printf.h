/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:07:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/12 01:27:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_flags {
	char	specifier;
	int		width;
	int		precision;
	int		zero_pad;
	int		left_align;
	char	positive_sign;
	int		hash;
	int		star;
	int		negative;
}		t_flags;

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_ptrlen(unsigned long int n);
void	parse_flags(const char *format, t_flags *flags, va_list args, int *i);
int		pad_width(int width, int size, int zero_pad);
int		print_c(char c);
int		is_type(char c);
int		is_digit(char c);
int		is_spec(char c);
int		is_flag(char c);
int		print_hex_handler(unsigned int nbr, int capital, t_flags *flags);
int		print_char(char c, t_flags flags);
int		print_ptr_handler(unsigned long int n, t_flags flags);
int		print_unsigned_handler(unsigned int nbr, t_flags flags);
int		print_nbr_handler(int nbr, t_flags *flags);
int		print_str(const char *str, t_flags flags);
int		print_s(const char *str);
int		ft_printf(const char *, ...);
char	*ft_itoa(long n);
char	*ft_xtoa(unsigned long int n, int capital);

#endif
