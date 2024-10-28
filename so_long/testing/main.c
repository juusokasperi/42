#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "mlx/mlx.h"

#define WIDTH 512
#define HEIGHT 512
#define MLX_ERROR 1
#define MLX_SUCCESS 0

typedef struct s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_env;

void	ft_put_pixel(t_env *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	ft_draw_line(t_env *data, int x1, int y1, int x2, int y2, int color)
{
	int	step;
	int	x;
	int	y;
	int	i;
	int	delta_x;
	int	delta_y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	if (abs(delta_x) >= abs(delta_y))
		step = abs(delta_x);
	else
		step = abs(delta_y);
	delta_x = delta_x / step;
	delta_y = delta_y / step;
	x = x1;
	y = x2;
	i = 0;
	while (i < step)
	{
		ft_put_pixel(data, x, y, color);
		x += delta_x;
		y += delta_y;
		i++;
	}
}

int main(void)
{
	t_env	data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (MLX_ERROR);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
		&data.line_length, &data.endian);
	ft_draw_line(&data, 5, 5, 400, 400, 0x00FF0000);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (MLX_SUCCESS);
}
