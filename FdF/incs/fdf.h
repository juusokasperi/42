/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:37:28 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/28 18:58:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "MLX42/MLX42.h"
# include "terminal_colors.h"

# define WIDTH 1080
# define HEIGHT 720
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define RED 0xFF0000FF
# define BLUE 0x0000FFFF

enum {
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	CENTER_X
};

typedef struct	s_draw
{
	double		x1;
	double		y1;
	double		x2;
	double		y2;
	double		x_step;
	double		y_step;
	int			max;
	uint32_t	color;
	uint32_t	color_1;
	uint32_t	color_2;
	int			z1;
	int			z2;
	double		fraction;
}				t_draw;

typedef struct	s_keys
{
	int	up;
	int	down;
	int	left;
	int	right;
}	t_keys;

typedef struct s_info
{
	int			width;
	int			height;
	int			**xyz;
	double		zoom;
	double		shift_x;
	double		shift_y;
	double		z_scale;
	double		angle;
	double		rotate;
	double		distance;
	int			projection;
	int			default_colors;
	int			highest_z;
	int			lowest_z;
	t_keys		keys;
	uint32_t	**colors;
	mlx_t		*mlx_ptr;
	mlx_image_t	*mlx_img;
}	t_info;

// Main.c
int		main(int argc, char **argv);
void	clear_image(t_info *data);
void	draw_instructions(t_info *data);
// Init
void	calculate_position(t_info *data);
int		init_data(t_info *data);
void	set_altitude(t_info *data);
// Read_map.c
int		read_map(char *filename, t_info *data);
// Read_map_utils.c
int		fill_xyz(int *z, char *line, t_info *data);
int		fill_colors(uint32_t *colors, char *line, t_info *data);
int		count_words(char *line);
int		get_height(char *filename);
int		get_width(char *filename);
// Draw.c
void	draw_lines(t_info *data);
// Draw_utils.c
void	init_info(t_draw *info, t_info *data);
void	set_x_y(double x, double y, t_draw *info, int x_or_y);
// Draw_utils_2.c
void	parallel(double *x, double *y, int z, t_info *data);
void	isometric(double *x, double *y, int z, t_info *data);
double	d_abs(double n);
// Controls.c
void	key_hook(mlx_key_data_t keydata, void *param);
// Exit.c
void	ft_exit(t_info *data);
void	ft_exit_error(int i, t_info *data);

#endif
