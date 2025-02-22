/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:18:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/22 16:01:47 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error(SYNTAX));
	if (!parse_args(&data, argc, argv))
		return (ft_error("Invalid arguments."));
	if (!init_mutexes(&data))
		return (ft_error("Error initializing mutexes."));
	if (!init_philos(&data))
		return (ft_error("Error initializing philosophers."));
	if (!init_threads(&data))
		return (1);
	monitor_routine(&data);
	if (!join_threads(&data))
		return (1);
	return (ft_cleanup(&data));
}

int	ft_error(char *str)
{
	printf("%sERROR:%s %s\n", TRED, TRESET, str);
	return (1);
}
