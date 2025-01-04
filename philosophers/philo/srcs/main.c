/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:18:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/03 23:39:17 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos = NULL;

	if (argc < 5 || argc > 6)
		ft_error("Invalid number of arguments.");
	if (!parse_args(&data, argc, argv))
		ft_error("Invalid arguments.");
	if (!init_mutexes(&data))
		ft_error("Error initializing mutexes.");
	if (!init_philos(&data, philos))
		ft_cleanup(&data, NULL, "Error initializing philosophers.");
	if (!init_threads(&data, philos))
		ft_cleanup(&data, philos, "Error initializing threads.");
	ft_cleanup(&data, philos, NULL);
	return (0);
}
