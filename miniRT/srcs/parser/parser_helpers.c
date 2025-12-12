/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:19:39 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/22 16:22:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	cleanup(t_data *data)
{
	free(data->scene.objects);
	free(data->scene.lights);
	return (true);
}

bool	validate_scene_content(t_data *data)
{
	if (data->camera_count > 1)
	{
		printf("Error\nScene must contain exactly one camera (C)\n");
		return (cleanup(data) && false);
	}
	if (data->ambient_count > 1)
	{
		printf("Error\nScene must contain max one ambient light (A)\n");
		return (cleanup(data) && false);
	}
	return (true);
}

bool	allocate_scene_memory(t_data *data)
{
	size_t	align;

	align = 16;
	if (data->scene.object_count > 0)
		data->scene.objects = (t_object *)arena_alloc_aligned(&data->arena,
			sizeof(t_object) * data->scene.object_count, align);
	if (data->scene.plane_count > 0)
		data->scene.planes = (t_object *)arena_alloc_aligned(&data->arena,
			sizeof(t_object) * data->scene.plane_count, align);
	if (data->scene.light_count > 0)
		data->scene.lights = (t_light *)arena_alloc_aligned(&data->arena,
			sizeof(t_light) * data->scene.light_count, align);
	data->scene.object_count = 0;
	data->scene.plane_count = 0;
	data->scene.light_count = 0;
	return (true);
}

bool	trim_line(char **line)
{
	char	*new;

	new = ft_strtrim(*line, " \t\n\r");
	free(*line);
	if (!new)
	{
		*line = NULL;
		return (false);
	}
	*line = new;
	return (true);
}
