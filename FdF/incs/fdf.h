/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:37:28 by jrinta-           #+#    #+#             */
/*   Updated: 2025/01/09 19:46:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "MLX42/MLX42.h"

# ifdef __APPLE__
#  define WIDTH 1024
#  define HEIGHT 666
# else
#  define WIDTH 2160
#  define HEIGHT 1440
# endif
# define INFO_W 256
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define RED 0xFF0000FF
# define BLUE 0x0000FFFF
# define TRANSPARENT 0x00000000

typedef struct s_bresenham
{
	int			start_x;
	int			start_y;
	int			x;
	int			y;
	int			x1;
	int			y1;
	int			diff_x;
	int			diff_y;
	int			step_x;
	int			step_y;
	int			max;
	int			err;
	int			err_2;
	int			z;
	int			z1;
	uint32_t	color_1;
	uint32_t	color_2;
}				t_bresenham;

typedef struct s_info
{
	int			width;
	int			height;
	int			**xyz;
	int			zoom;
	int			shift_x;
	int			shift_y;
	int			z_scale;
	float		x_angle;
	float		y_angle;
	float		z_angle;
	int			projection;
	int			default_colors;
	int			highest_z;
	int			lowest_z;
	uint32_t	**colors;
	mlx_t		*mlx_ptr;
	mlx_image_t	*mlx_img;
}	t_info;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_color;

// Main.c
void		clear_image(t_info *data);
// Init.c
void		init_variables(t_info *data);
void		calculate_cam(t_info *data);
void		init_data(t_info *data);
void		set_altitude(t_info *data);
void		reset_angles(t_info *data);
// Info.c
void		draw_instructions(t_info *data);
// Read_map.c
int			read_map(char *filename, t_info *data);
// Read_map_utils.c
int			fill_xyz(int *z, char *line, t_info *data);
int			fill_colors(uint32_t *colors, char *line, t_info *data);
// Read_map_utils_2.c
int			count_words(char *line);
int			get_height(char *filename);
int			get_width(char *filename);
// Draw.c
void		draw_lines(t_info *data);
// Draw_utils.c
void		set_xy(t_bresenham *line, int x, int y, int x_or_y);
void		zoom(t_bresenham *line, t_info *data);
void		calculate_bresenham(t_bresenham *line);
void		shift(t_bresenham *line, t_info *data);
void		set_projection(t_bresenham *line, t_info *data);
// Colors.c
void		set_colors(t_bresenham *line, t_info *data);
uint32_t	interpolate_color(t_bresenham *line);
// Transformations.c
void		isometric(int *x, int *y, int *z, t_info *data);
void		orthographic(int *x, int *y, int z, t_info *data);
// Controls.c
void		loop_hook(void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
// Exit.c
void		ft_exit(t_info *data);
void		ft_exit_error(int i, t_info *data);

#endif
