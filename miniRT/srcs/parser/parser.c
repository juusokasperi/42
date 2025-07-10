/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:42:45 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/22 16:22:52 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	process_identifier(char *identifier, t_line_context *ctx)
{
	bool	result;
	char	*current_line;

	current_line = ctx->line;
	if (ft_strncmp(identifier, "A", 1) == 0)
		result = parse_ambient(&current_line[ctx->idx], ctx->data);
	else if (ft_strncmp(identifier, "C", 1) == 0)
		result = parse_camera(&current_line[ctx->idx], ctx->data);
	else if (ft_strncmp(identifier, "L", 1) == 0)
		result = parse_light(&current_line[ctx->idx], ctx->data);
	else if (ft_strncmp(identifier, "sp", 2) == 0)
		result = parse_sphere(&current_line[ctx->idx], ctx);
	else if (ft_strncmp(identifier, "pl", 2) == 0)
		result = parse_plane(&current_line[ctx->idx], ctx);
	else if (ft_strncmp(identifier, "cy", 2) == 0)
		result = parse_cylinder(&current_line[ctx->idx], ctx);
	else if (ft_strncmp(identifier, "co", 2) == 0)
		result = parse_cone(&current_line[ctx->idx], ctx);
	else
	{
		printf("Error\nUnknown identifier in line: %s\n", current_line);
		result = false;
	}
	return (result);
}

static bool	parse_line(char *line, t_data *data)
{
	t_line_context	ctx;
	char			*identifier;
	bool			result;

	if (!line || line[0] == '\0' || line[0] == '#')
		return (true);
	identifier = NULL;
	ctx.scale = 1.0f;
	ctx.color_2 = rgb(225, 225, 225);
	ctx.is_checkered = false;
	ctx.idx = 0;
	ctx.line = line;
	ctx.data = data;
	if (!parse_identifier(line, &identifier, &ctx))
	{
		printf("Error\nInvalid identifier in line: %s\n", line);
		return (false);
	}
	result = process_identifier(identifier, &ctx);
	free(identifier);
	return (result);
}

static bool	process_trimmed_line(char *trimmed, t_data *data)
{
	if (trimmed && trimmed[0] != '\0' && trimmed[0] != '#')
	{
		if (trimmed[0] == 'A')
			data->ambient_count++;
		else if (trimmed[0] == 'C')
			data->camera_count++;
		else if (trimmed[0] == 'L')
			data->scene.light_count++;
		else if (ft_strncmp(trimmed, "sp", 2) == 0 || ft_strncmp(trimmed,
				"pl", 2) == 0 || ft_strncmp(trimmed, "cy", 2) == 0
			|| ft_strncmp(trimmed, "co", 2) == 0)
			data->scene.object_count++;
	}
	return (true);
}

static bool	count_scene_elements(const char *filename, t_data *data)
{
	int		fd;
	char	*line;
	char	*trimmed;

	if (!validate_scene_file(filename, &fd))
		return (false);
	data->scene.object_count = 0;
	data->scene.light_count = 0;
	data->camera_count = 0;
	data->ambient_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \t\n\r");
		process_trimmed_line(trimmed, data);
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}

bool	parse_scene(const char *filename, t_data *data)
{
	int		fd;
	char	*line;
	bool	result;

	if (!count_scene_elements(filename, data))
		return (false);
	if (!allocate_scene_memory(data))
		return (false);
	if (!validate_scene_file(filename, &fd))
		return (cleanup(data) && false);
	result = true;
	line = get_next_line(fd);
	while (line && result)
	{
		if (!trim_line(&line))
			return (cleanup(data) && false);
		result = parse_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!result)
		return (cleanup(data) && false);
	return (validate_scene_content(data));
}
