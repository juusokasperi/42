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
	data->scene.objects = (t_object *)malloc(sizeof(t_object)
			* data->scene.object_count);
	if (!data->scene.objects)
	{
		printf("Error\nFailed to allocate memory for objects\n");
		return (false);
	}
	data->scene.lights = (t_light *)malloc(sizeof(t_light)
			* data->scene.light_count);
	if (!data->scene.lights)
	{
		free(data->scene.objects);
		printf("Error\nFailed to allocate memory for lights\n");
		return (false);
	}
	data->scene.object_count = 0;
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
