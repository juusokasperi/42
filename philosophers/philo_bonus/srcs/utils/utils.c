/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:21:11 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/11 15:13:19 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

size_t	time_now(t_data *data)
{
	return (get_time_ms() - data->start_time);
}

size_t	time_since_meal(t_philo *philo)
{
	return (time_now(philo->data) - philo->last_meal);
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
		usleep(500);
	return (0);
}

void	*ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}
