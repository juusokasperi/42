/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:31:35 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/13 17:03:02 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	allocate_z_colors(t_info *data);
static int	read_z_colors(char *filename, t_info *data);
static int	fill_z(int *z, char *line, t_info *data);
static int	fill_colors(uint32_t *colors, char *line, t_info *data);

void	read_map(char *filename, t_info *data)
{
	init_variables(data);
	data->height = get_height(filename);
	data->width = get_width(filename);
	if (data->width == -1 || data->height == 0)
		ft_exit_error(4, data);
	if (!allocate_z_colors(data))
		ft_exit_error(3, data);
	if (!read_z_colors(filename, data))
		ft_exit_error(6, data);
	calculate_zoom(data);
}

// Allocates enough space for the 2D arrays "colors" and "xyz"
// Returns 1 if success, 0 if fail. All freeing is done during exit.
static int	allocate_z_colors(t_info *data)
{
	int		i;

	data->colors = malloc(sizeof(uint32_t *) * (data->height));
	if (!data->colors)
		return (0);
	data->xyz = malloc(sizeof(int *) * (data->height));
	if (!data->xyz)
		return (0);
	i = -1;
	while (++i < data->height)
	{
		data->colors[i] = malloc(sizeof(uint32_t) * (data->width));
		if (!data->colors[i])
			return (0);
		data->xyz[i] = malloc(sizeof(int) * (data->width));
		if (!data->xyz[i])
			return (0);
	}
	return (1);
}

// Reads through the file using get_next_line and calling fill_colors()
// and fill_z() functions.
// Returns 1 if success, 0 if fail. All freeing is done during exit.
static int	read_z_colors(char *filename, t_info *data)
{
	int		fd;
	int		i;
	char	*line;

	i = -1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	while (++i < data->height)
	{
		line = get_next_line(fd);
		if (!fill_colors(data->colors[i], line, data)
			|| !fill_z(data->xyz[i], line, data))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (1);
}

// Splits the passed string "line" and calls atoi on each member.
// Also sets highest_z and lowest_z values that are used later for
// calculating a default z altitude.
static int	fill_z(int *z, char *line, t_info *data)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	while (split[i])
	{
		z[i] = ft_atoi(split[i]);
		if (z[i] > data->highest_z)
			data->highest_z = z[i];
		if (z[i] < data->lowest_z)
			data->lowest_z = z[i];
		i++;
	}
	free_split(split);
	return (1);
}

// Splits the passed string "line" first by ' ' and then splits that
// by ','. If there is a color value after the ',', it is stored,
// else it is set to WHITE color.
static int	fill_colors(uint32_t *colors, char *line, t_info *data)
{
	char		**split;
	char		**colors_split;
	int			i;

	i = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	while (split[i])
	{
		colors_split = ft_split(split[i], ',');
		if (!colors_split)
			return (free_split(split));
		if (colors_split[1] && color_is_valid(colors_split[1]))
		{
			colors[i] = hex_to_rgba(colors_split[1]);
			data->default_colors = 0;
		}
		else
			colors[i] = WHITE;
		free_split(colors_split);
		i++;
	}
	free_split(split);
	return (1);
}
