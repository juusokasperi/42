/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:59:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/03 22:09:47 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_success(void);

void	ft_cleanup(t_data *data, t_philo *philos, char *str)
{
	int	i;

	if (data)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			if (philos)
				pthread_mutex_destroy(&philos[i].meal_mutex);
			if (data->forks)
				pthread_mutex_destroy(&data->forks[i]);
		}
		pthread_mutex_destroy(&data->dead_lock);
		if (data->forks)
			free(data->forks);
	}
	if (philos)
		free(philos);
	if (str)
		ft_error(str);
	else
		ft_success();
}

static void	ft_success(void)
{
	printf("%sSUCCESS:%s All philosophers have finished eating.\n",
			TGREEN, TRESET);
	exit(0);
}
