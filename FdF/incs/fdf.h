/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:37:28 by jrinta-           #+#    #+#             */
/*   Updated: 2024/12/08 19:16:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "MLX42/MLX42.h"
# include "terminal_colors.h"

# define WIDTH 640
# define HEIGHT 640

typedef struct s_info
{
	int			width;
	int			height;
	int			**xyz;
	char		***colors;
	mlx_t		*mlx_ptr;
	mlx_image_t	*mlx_img;
}	t_info;

// Main.c
int		main(int argc, char **argv);
// Read_map.c
int		read_map(char *filename, t_info *data);
// Read_map_utils.c
int		count_words(char *line);
int		get_height(char *filename);
int		get_width(char *filename);
int		get_colors(char *filename, t_info *data);
int		get_xyz(char *filename, t_info *data);
// Draw.c
void	draw(float x1, float y1, float x2, float y2, t_info *fdf);
//void draw(int x1, int y1, int x2, int y2, t_info *data);

#endif
