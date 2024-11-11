/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:07:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 19:47:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

size_t	str_len(const char *s);
char	*str_dup(const char *s1);
int		print_c(char c);
int		is_type(char c);
int		is_digit(char c);
int		is_spec(char c);
int		is_flag(char c);
int		print_hex_handler(unsigned int nbr, int capital);
int		print_ptr_handler(unsigned long int n);
int		print_unsigned_handler(unsigned int nbr);
int		print_nbr_handler(int nbr);
int		print_str_handler(const char *str);
int		print_s(const char *str);
int		ft_printf(const char *, ...);
char	*ft_ltoa(long n);
char	*ft_xtoa(unsigned long int n, int capital);

#endif
