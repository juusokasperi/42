/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:36:39 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/15 14:42:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>

# define DELAY 10000
# define DELAY_LONG 50000
# define RETRY_LIMIT 5
# define BUFFER_SIZE 1024

typedef struct s_buffer
{
	char	received_char;
	int		bit_count;
	char	*str;
	size_t	size;
	size_t	index;
}	t_buffer;

#endif
