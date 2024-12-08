/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:38:00 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/08 20:14:29 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ft_exit(int i)
{
	char *error_message;

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
	ft_printf("%sERROR:%s ", RED, RESET);
	ft_printf("%s\n", error_message);
	exit(1);
}

int	valid_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	init_data(t_info *data)
{
	data->width = 0;
	data->height = 0;
	data->xyz = NULL;
	data->colors = NULL;
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "FdF jrinta-42", true);
	data->mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->mlx_ptr || !data->mlx_img
		|| (mlx_image_to_window(data->mlx_ptr, data->mlx_img, 0, 0) < 0))
	{
		free(data);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	*data;
	int		i;

	if (argc != 2)
		ft_exit(1);
	data = (t_info *)malloc(sizeof(t_info));
	if (!data)
		ft_exit(3);
	if (!valid_file(argv[1]))
		ft_exit(2);
	if (!init_data(data))
		ft_exit(3);
	i = read_map(argv[1], data);
	if (i)
	{
		free(data);
		ft_exit(i);
	}
	draw(10, 10, 600, 10, data);
	draw(11, 11, 600, 11, data);
	draw(12, 12, 600, 12, data);
	draw(13, 13, 600, 13, data);
	draw(14, 14, 600, 14, data);
//	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
	return (0);
}
