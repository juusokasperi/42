/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:18:41 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/17 13:45:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_data *data)
{
	pthread_t	monitor;
	int			i;

	data->start_time = get_time_ms();
	if (pthread_create(&monitor, NULL, &monitor_routine, data) != 0)
		return (0);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
			return (0);
	}
	if (pthread_join(monitor, NULL) != 0)
		return (0);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
	return (1);
}
