/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:59:45 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/03 22:06:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < ms)
		usleep(500);
	return (0);
}
