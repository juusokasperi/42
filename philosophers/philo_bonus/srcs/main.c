/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:18:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/12 12:32:22 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	close_and_unlink_semaphores(t_data *data);
int		create_fork(void);

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;
	pid_t	pid;

	if (argc < 5 || argc > 6)
		return (ft_error(SYNTAX));
	if (!parse_args(&data, argc, argv))
		return (ft_error("Invalid arguments."));
	if (init_semaphores(&data) == -1)
		return (1);
	i = -1;
	while (++i < data.philo_count)
	{
		data.philo->id++;
		pid = create_fork();
		if (pid == 0)
			philo_routine(&data);
		data.philo_pids[i] = pid;
	}
	wait_children(&data);
	close_and_unlink_semaphores(&data);
	ft_free((void **)&data.philo_pids);
	return (0);
}

int	ft_error(char *str)
{
	printf("%sERROR:%s %s\n", "\033[91m", "\033[0m", str);
	return (1);
}
