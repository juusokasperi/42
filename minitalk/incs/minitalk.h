/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:36:39 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/27 16:59:58 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>

# define DELAY 50000
# define RETRY_LIMIT 5
# define BUFFER_SIZE 1024

typedef struct	s_buffer
{
	char	*str;
	size_t	size;
	size_t	index;
}	t_buffer;

#endif
