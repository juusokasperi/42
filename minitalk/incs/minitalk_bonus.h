/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:16:35 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/25 17:17:06 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "minitalk.h"

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
