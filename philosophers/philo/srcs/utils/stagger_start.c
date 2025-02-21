/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stagger_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:10:28 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/21 22:18:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	stagger_start(t_philo *philo)
{
	if (philo->data->philo_count % 2)
		ft_usleep(philo->data->time_to_eat * philo->id \
			/ philo->data->philo_count);
	else if (philo->id % 2)
		ft_usleep(philo->data->time_to_eat / 2);
}
