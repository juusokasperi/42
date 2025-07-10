/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:53:52 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/19 17:47:48 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	parse_sphere(char *line, t_line_context *ctx)
{
	char			**parts;
	t_object		*sphere;
	t_data			*data;
	float			diameter;

	data = ctx->data;
	if (!line || !data || !validate_object_count(data))
		return (false);
	parts = ft_split_isspace(line);
	if (!validate_and_init_object(data, &sphere, parts, SPHERE)
		|| !parse_object_position(parts, &sphere->data.sphere.center)
		|| !parse_positive_float(parts, 1, &diameter,
			"Sphere diameter must be positive")
		|| !parse_object_color(parts[2], sphere, ctx->is_checkered,
			&ctx->color_2))
	{
		free_split(parts);
		return (false);
	}
	sphere->data.sphere.radius = diameter / 2;
	setup_checkered_object(sphere, ctx);
	free_split(parts);
	data->scene.object_count++;
	return (true);
}
