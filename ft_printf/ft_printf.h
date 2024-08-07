/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:07:43 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/07 20:28:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int	print_char(char c);
int	print_hex(unsigned int nbr, int capital);
int	print_char(char c);
int	print_ptr(unsigned long int n);
int	print_unsigned(unsigned int nbr);
int	print_nbr(int nbr);
int	print_str(const char *str);
int	ft_printf(const char *, ...);

#endif
