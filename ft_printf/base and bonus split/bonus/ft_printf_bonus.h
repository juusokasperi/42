/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:07:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/11 14:18:19 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_flags
{
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

size_t	str_len(const char *s);
char	*str_dup(const char *s1);
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
int		print_str_handler(const char *str, t_flags flags);
int		print_s(const char *str);
int		ft_printf(const char *, ...);
char	*ft_ltoa(long n);
char	*ft_xtoa(unsigned long int n, int capital);

#endif
