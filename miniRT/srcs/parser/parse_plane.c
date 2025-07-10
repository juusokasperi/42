/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:10:36 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/02 20:23:32 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	parse_plane(char *line, t_line_context *ctx)
{
	char			**parts;
	t_object		*plane;
	t_data			*data;

	data = ctx->data;
	if (!line || !data || !validate_object_count(data))
		return (false);
	parts = ft_split_isspace(line);
	if (!validate_and_init_object(data, &plane, parts, PLANE)
		|| !parse_object_position(parts, &plane->data.plane.point)
		|| !parse_object_direction(parts, &plane->data.plane.normal)
		|| !parse_object_color(parts[2], plane, ctx->is_checkered,
			&ctx->color_2))
	{
		free_split(parts);
		return (false);
	}
	setup_checkered_object(plane, ctx);
	free_split(parts);
	data->scene.object_count++;
	return (true);
}
