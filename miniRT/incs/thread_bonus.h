/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:09:05 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/10 18:28:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_BONUS_H
# define THREAD_BONUS_H

# include <pthread.h>
# include "structs.h"
# include "mini_rt.h"

# ifndef NUM_THREADS
#  define NUM_THREADS 4
# endif

# define TILE_SIZE 128

typedef struct s_tile
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_tile;

typedef struct s_thread_context
{
	t_data			*data;
	int				thread_count;
	int				next_tile;
	pthread_mutex_t	tile_mutex;
}	t_thread_context;

int		get_system_thread_count(void);
void	print_threading_info(int thread_count);
void	raycast_threaded(t_data *data, int thread_count);
void	*thread_tile_worker(void *arg);

#endif
