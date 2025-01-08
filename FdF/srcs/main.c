/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:38:00 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/08 18:11:16 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	valid_file(char *filename);
void		clear_image(t_info *data);
void		draw_instructions(t_info *data);

int	main(int argc, char **argv)
{
	t_info	*data;
	int		i;

	if (argc != 2)
		ft_exit_error(1, NULL);
	if (!valid_file(argv[1]))
		ft_exit_error(2, NULL);
	data = (t_info *)malloc(sizeof(t_info));
	if (!data)
		ft_exit_error(3, NULL);
	i = read_map(argv[1], data);
	if (i != 0)
		ft_exit_error(i, data);
	if (!init_data(data))
		ft_exit_error(3, data);
	set_altitude(data);
	draw_lines(data);
	mlx_key_hook(data->mlx_ptr, &key_hook, data);
	mlx_loop_hook(data->mlx_ptr, &loop_hook, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
	ft_exit(data);
	return (0);
}

static int	valid_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
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

void	draw_instructions(t_info *data)
{
	mlx_put_string(data->mlx_ptr, "Arrow keys: Move", 10, 10);
	mlx_put_string(data->mlx_ptr, "Q/W: Altitude (z-scale)", 200, 10);
	mlx_put_string(data->mlx_ptr, "R: Reset rotation", 450, 10);
	mlx_put_string(data->mlx_ptr, "C: Colors", 700, 10);
	mlx_put_string(data->mlx_ptr, "ESC: Exit", 900, 10);
	mlx_put_string(data->mlx_ptr, "1/2: Rotate X", 10, 30);
	mlx_put_string(data->mlx_ptr, "3/4: Rotate Y", 200, 30);
	mlx_put_string(data->mlx_ptr, "5/6: Rotate Z", 450, 30);
	mlx_put_string(data->mlx_ptr, "Z/X: Zoom", 700, 30);
	mlx_put_string(data->mlx_ptr, "P: Projection", 900, 30);
}
