/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:32:15 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/03 23:39:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_msg(t_philo *philo, char *str)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->dead_lock);
	time = get_time_ms();
	printf("%zu %d %s\n", time - philo->data->start_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->dead_lock);
}
