/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:32:15 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/17 13:46:59 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_msg(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->dead_lock);
	time = get_time_ms();
	if (printf("%zu %d %s\n", time - philo->data->start_time, \
		philo->id, str) == -1)
	{
		philo->data->error = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}
