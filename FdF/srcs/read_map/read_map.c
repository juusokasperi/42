/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:31:35 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/08 17:58:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Tarvitaan free -funktio; jos colors_handler feilaa, niin xyz_handlerin
// data->xyz pitaa vapauttaa

static int	xyz_handler(char *filename, t_info *data);
static int	colors_handler(char *filename, t_info *data);

int	read_map(char *filename, t_info *data)
{
	data->width = get_width(filename);
	data->height = get_height(filename);
	if (data->width == -1 || data->height == -1)
		return (4);
	if (!xyz_handler(filename, data))
		return (3);
	if (!colors_handler(filename, data))
		return (3);
	return (0);
}

static int	colors_handler(char *filename, t_info *data)
{
	int		i;

	data->colors = malloc(sizeof(char **) * data->height + 1);
	if (!data->colors)
		return (0);
	i = -1;
	while (++i <= data->height)
	{
		data->colors[i] = malloc(sizeof(char *) * (data->width + 1));
		if (!data->colors[i])
		{
			while (i > 0)
				free(data->colors[--i]);
			free(data->colors);
			return (0);
		}
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
		{
			while (i > 0)
				free(data->xyz[--i]);
			free(data->xyz);
			return (0);
		}
	}
	if (!get_xyz(filename, data))
		return (0);
	return (1);
}
