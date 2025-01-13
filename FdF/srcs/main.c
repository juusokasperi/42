/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:38:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/13 19:41:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	valid_file(char *filename);

int	main(int argc, char **argv)
{
	t_info	*data;

	if (argc != 2)
		ft_exit_error(1, NULL);
	if (!valid_file(argv[1]))
		ft_exit_error(2, NULL);
	data = (t_info *)malloc(sizeof(t_info));
	if (!data)
		ft_exit_error(3, NULL);
	read_map(argv[1], data);
	init_data(data);
	set_altitude(data);
	draw_lines(data);
	mlx_key_hook(data->mlx_ptr, &key_hook, data);
	mlx_loop_hook(data->mlx_ptr, &loop_hook, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
	ft_exit(data);
	return (0);
}

void	clear_image(t_info *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(data->mlx_img, x, y, BLACK);
	}
}

static int	valid_file(char *filename)
{
	int		fd;
	char	buffer[1];
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + (len - 4), ".fdf", 4) != 0)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	if (read(fd, buffer, 1) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
