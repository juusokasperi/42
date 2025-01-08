/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:31:35 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/08 18:11:00 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Tarvitaan free -funktio; jos colors_handler feilaa, niin xyz_handlerin
// data->xyz pitaa vapauttaa

static int	xyz_handler(char *filename, t_info *data);
static int	get_xyz(char *filename, t_info *data);
static int	colors_handler(char *filename, t_info *data);
static int	get_colors(char *filename, t_info *data);

int	read_map(char *filename, t_info *data)
{
	init_variables(data);
	data->height = get_height(filename);
	data->width = get_width(filename);
	if (data->width == -1 || data->height == 0)
		return (4);
	if (!xyz_handler(filename, data))
		return (3);
	if (!colors_handler(filename, data))
		return (3);
	calculate_cam(data);
	return (0);
}

static int	colors_handler(char *filename, t_info *data)
{
	int		i;

	data->colors = malloc(sizeof(uint32_t *) * data->height + 1);
	if (!data->colors)
		return (0);
	i = -1;
	while (++i <= data->height)
	{
		data->colors[i] = malloc(sizeof(uint32_t) * (data->width + 1));
		if (!data->colors[i])
			return (0);
	}
	if (!get_colors(filename, data))
		return (0);
	return (1);
}

static int	xyz_handler(char *filename, t_info *data)
{
	int		i;

	data->xyz = malloc(sizeof(int *) * data->height + 1);
	if (!data->xyz)
		return (0);
	i = -1;
	while (++i <= data->height)
	{
		data->xyz[i] = malloc(sizeof(int) * (data->width + 1));
		if (!data->xyz[i])
			return (0);
	}
	if (!get_xyz(filename, data))
		return (0);
	return (1);
}

static int	get_colors(char *filename, t_info *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!fill_colors(data->colors[i], line, data))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	data->colors[i] = NULL;
	return (1);
}

static int	get_xyz(char *filename, t_info *data)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (!fill_xyz(data->xyz[i], line, data))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	data->xyz[i] = NULL;
	return (1);
}
