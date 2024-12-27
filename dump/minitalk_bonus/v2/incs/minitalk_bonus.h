/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:16:35 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/26 15:52:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "minitalk.h"

typedef struct	s_signal_state
{
	int				client_pid;
	unsigned char	received_char[4];
	int				byte_count;
	int				bit_count;
	int				expected_bytes;
	t_buffer		buffer;
}	t_signal_state;

#endif
