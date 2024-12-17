/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:38:00 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/15 20:56:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	valid_file(char *filename);
void		clear_image(t_info *data);

int	main(int argc, char **argv)
{
	t_info	*data;
	int		i;

	data = NULL;
	if (argc != 2)
		ft_exit_error(1, data);
	if (!valid_file(argv[1]))
		ft_exit_error(2, data);
	data = (t_info *)malloc(sizeof(t_info));
	if (!data)
		ft_exit_error(3, data);
	if (!init_data(data))
		ft_exit_error(3, data);
	i = read_map(argv[1], data);
	if (i != 0)
		ft_exit_error(i, data);
	calculate_zoom(data);
	draw_lines(data);
	mlx_key_hook(data->mlx_ptr, &key_hook, data);
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
			mlx_put_pixel(data->mlx_img, x, y, 0x000000FF);
	}
}
