/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:33:35 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/09 19:34:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static uint32_t	hex_to_rgba(const char *hex);
static int		free_split(char **split);

int	fill_xyz(int *z, char *line, t_info *data)
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

int	fill_colors(uint32_t *colors, char *line, t_info *data)
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
		if (colors_split[1])
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

static uint32_t	hex_to_rgba(const char *hex)
{
	uint32_t	rgb;

	rgb = (uint32_t)ft_strtol(hex, NULL, 16);
	return (rgb << 8 | 0xFF);
}

static int	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (0);
}
