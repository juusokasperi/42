/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:26:12 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/16 13:34:59 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	parse_cone_attrs(char **parts, t_object *cone,
				t_line_context *ctx)
{
	if (!parse_object_position(parts, &cone->data.cylinder.center)
		|| !parse_object_direction(parts, &cone->data.cylinder.axis)
		|| !parse_positive_float(parts, 2, &cone->data.cylinder.radius,
			"Cone radius must be positive")
		|| !parse_positive_float(parts, 3, &cone->data.cylinder.height,
			"Cone height must be positive")
		|| !parse_object_color(parts[4], cone, ctx->is_checkered,
			&ctx->color_2))
		return (false);
	cone->data.cone.radius /= 2.0;
	setup_checkered_object(cone, ctx);
	return (true);
}

bool	parse_cone(char *line, t_line_context *ctx)
{
	char			**parts;
	t_object		*cone;
	t_data			*data;

	data = ctx->data;
	if (!line || !data || !validate_object_count(data))
		return (false);
	parts = ft_split_isspace(line);
	if (!validate_and_init_object(data, &cone, parts, CONE)
		|| !parse_cone_attrs(parts, cone, ctx))
	{
		free_split(parts);
		return (false);
	}
	free_split(parts);
	data->scene.object_count++;
	return (true);
}
