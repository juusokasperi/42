/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:10:09 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/02 20:22:07 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	parse_cylinder_attrs(char **parts, t_object *cylinder,
				t_line_context *ctx)
{
	if (!parse_object_position(parts, &cylinder->data.cylinder.center)
		|| !parse_object_direction(parts, &cylinder->data.cylinder.axis)
		|| !parse_positive_float(parts, 2, &cylinder->data.cylinder.radius,
			"Cylinder radius must be positive")
		|| !parse_positive_float(parts, 3, &cylinder->data.cylinder.height,
			"Cylinder height must be positive")
		|| !parse_object_color(parts[4], cylinder, ctx->is_checkered,
			&ctx->color_2))
		return (false);
	cylinder->data.cylinder.radius /= 2.0;
	setup_checkered_object(cylinder, ctx);
	return (true);
}

bool	parse_cylinder(char *line, t_line_context *ctx)
{
	char			**parts;
	t_object		*cylinder;
	t_data			*data;

	data = ctx->data;
	if (!line || !data || !validate_object_count(data))
		return (false);
	parts = ft_split_isspace(line);
	if (!validate_and_init_object(data, &cylinder, parts, CYLINDER)
		|| !parse_cylinder_attrs(parts, cylinder, ctx))
	{
		free_split(parts);
		return (false);
	}
	free_split(parts);
	data->scene.object_count++;
	return (true);
}
