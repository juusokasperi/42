/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:32:15 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/20 19:26:05 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_msg(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->print_lock);
	if (is_dead(philo) && ft_strcmp(str, "died") != 0)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return (-1);
	}
	time = get_time_ms();
	if (printf("%zu %d %s\n", time - philo->data->start_time, \
		philo->id, str) == -1)
	{
		philo->data->error = 1;
		pthread_mutex_unlock(&philo->data->print_lock);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
	return (0);
}
