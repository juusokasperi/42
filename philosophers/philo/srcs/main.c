/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:18:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/21 17:35:02 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		ft_error(SYNTAX);
	if (!parse_args(&data, argc, argv))
		ft_error("Invalid arguments.");
	if (!init_mutexes(&data))
		ft_error("Error initializing mutexes.");
	if (!init_philos(&data))
		ft_error("Error initializing philosophers.");
	if (!init_threads(&data))
		ft_error("Error initializing threads.");
	monitor_routine(&data);
	if (!join_threads(&data))
		ft_error("Error joining threads.");
	ft_cleanup(&data, NULL);
	return (0);
}
