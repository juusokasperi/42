/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:18:41 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/03 23:39:18 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_data *data, t_philo *philos)
{
	pthread_t	monitor;
	int			i;

	if (pthread_create(&monitor, NULL, &monitor_routine, philos) != 0)
		return (0);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_create(&philos[i].thread, NULL, &philo_routine, &philos[i]) != 0)
			return (0);
	if (pthread_join(monitor, NULL) != 0)
		return (0);
	i = -1;
	while (++i < data->philo_count)
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (0);
	return (1);
}
