/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:36:39 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/24 17:55:32 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>

typedef struct	s_signal_state
{
	int				client_pid;
	unsigned char	buffer[4];
	int				byte_count;
	int				bit_count;
	int				expected_bytes;
	int				total_bytes;
}	t_signal_state;

#endif
