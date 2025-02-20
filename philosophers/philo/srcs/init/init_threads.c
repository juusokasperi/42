/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:18:41 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/20 17:01:16 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
			return (0);
	}
	monitor_routine(data);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
	return (1);
}
