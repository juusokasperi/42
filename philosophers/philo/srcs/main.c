/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:18:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/12 18:43:52 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		ft_error("Invalid number of arguments.");
	if (!parse_args(&data, argc, argv))
		ft_error("Invalid arguments.");
	if (!init_mutexes(&data))
		ft_error("Error initializing mutexes.");
	if (!init_philos(&data))
		ft_cleanup(&data, "Error initializing philosophers.");
	if (!init_threads(&data))
		ft_cleanup(&data, "Error initializing threads.");
	ft_cleanup(&data, NULL);
	return (0);
}
