/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:00:00 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/17 16:17:22 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "thread_bonus.h"

void	setup_rendering(t_data *data)
{
	init_data(data);
	data->cam_controls = init_cam_controls();
	data->thread_count = get_system_thread_count();
	print_controls();
	fill_black(data);
	raycast_threaded(data, data->thread_count);
}
