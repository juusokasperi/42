/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:47:19 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/17 19:13:02 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_xyz(t_info *data);
static void	free_colors(t_info *data);

void	ft_exit(t_info *data)
{
	if (data)
	{
		free_xyz(data);
		free_colors(data);
		free(data);
	}
	exit(1);
}

void	ft_exit_error(int i, t_info *data)
{
	char	*error_message;

	if (i == 1)
		error_message = "Usage: ./fdf <file_to_read>";
	else if (i == 2)
		error_message = "Invalid file.";
	else if (i == 3)
		error_message = "Malloc failed.";
	else if (i == 4)
		error_message = "Found wrong line length. Exiting.";
	else
		error_message = "Unknown error.";
	ft_printf("%sERROR:%s ", TRED, TRESET);
	ft_printf("%s\n", error_message);
	ft_exit(data);
}

static void	free_xyz(t_info *data)
{
	int	y;

	if (data->xyz)
	{
		y = 0;
		while (y < data->height)
		{
			if (data->xyz[y])
				ft_free((void **)&data->xyz[y]);
			y++;
		}
		ft_free((void **)&data->xyz);
	}
}

static void	free_colors(t_info *data)
{
	int	y;

	if (data->colors)
	{
		y = 0;
		while (y < data->height)
		{
			if (data->colors[y])
				ft_free((void **)&data->colors[y]);
			y++;
		}
		ft_free((void **)&data->colors);
	}
}
