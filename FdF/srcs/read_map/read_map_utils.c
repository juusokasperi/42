/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:33:35 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/08 17:51:42 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Tarviiko vielä error handlingin jos esim get_next_line palauttaa NULL heti?

static int	fill_xyz(int *z, char *line)
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
		free(split[i]);
		i++;
	}
	free(split);
	return (1);
}

static int	fill_colors(char **color, char *line)
{
	char	**split;
	char	**colors_split;
	int		i;

	i = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	while (split[i])
	{
		colors_split = ft_split(split[i], ',');
		if (!colors_split)
		{
			free(split[i]);
			return (0);
		}
		if (colors_split[1])
		{
			color[i] = ft_strdup(colors_split[1]);
			free(colors_split[1]);
		}
		else
			color[i] = ft_strdup("0xFFFFFF");
		free(split[i]);
		free(colors_split[0]);
		free(colors_split);
		i++;
	}
	free(split);
	return (1);
}

int	get_colors(char *filename, t_info *data)
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
		if (!fill_colors(data->colors[i], line))
		{
			while (i > 0)
				free(data->colors[--i]);
			free(data->colors);
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

int	get_xyz(char *filename, t_info *data)
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
		if (!fill_xyz(data->xyz[i], line))
		{
			while (i > 0)
				free(data->xyz[--i]);
			free(data->xyz);
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
