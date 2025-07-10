/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:53:22 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/22 16:58:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h> // for printf
# include <unistd.h> // for read, close.
# include <fcntl.h> // for open
# include "libft.h"
# include "structs.h"
# include "parser.h"
# include "bvh.h"
# define WIDTH 800
# define HEIGHT 640
# define BOTTOM_DISK 0
# define TOP_DISK 1
# define X 0
# define Y 1
# define Z 2
# ifndef FLT_MAX
#  define FLT_MAX 340282346638528859811704183484516925440.0
# endif
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define EPSILON 0.0001f
# define SHADOW_EPSILON 0.001f
# define PLANE_EPSILON 0.00001f

//	color/calculate_color.c
t_rgb			calculate_color(t_data *data, t_object obj, t_ray ray, float t);
void			fill_black(t_data *data);
//	color/checkerboard.c
void			check_checkerboard(t_object *obj, t_point point);

//	hooks/resize.c
void			resize_hook(int width, int height, void *param);
//	hooks/camera_movement.c && camera_rotation.c
bool			handle_camera_movement(t_data *data);
bool			handle_camera_rotation(t_data *data);
//	hooks/camera_controls.c
t_cam_controls	init_cam_controls(void);
void			update_camera(t_data *data);
void			print_controls(void);
void			loop_hook(void *param);

//	intersect/intersect.c
float			ray_intersect(t_ray ray, t_object *object);
//	intersect/cylinder.c
float			cylinder_ray_intersect(t_ray ray, t_cylinder *cylinder);
//	intersect/cone.c && cone_2.c
float			cone_ray_intersect(t_ray ray, t_cone *cone);
t_ray			transform_ray_cone(t_ray ray, t_cone cone);

//	raycast/raycast.c
void			raycast(t_data *data);

//	rgb_utils/rgb.c && rgb_2.c
t_rgb			rgb_scalar(t_rgb a, t_rgb b);
t_rgb			rgb_scalar_multiply(t_rgb a, float scalar);
t_rgb			rgb_add(t_rgb a, t_rgb b);
t_rgb			rgb(int r, int g, int b);
uint32_t		rgb_to_uint(t_rgb a);

//	shadows/shadow_check.c && shadow_check_2.c
bool			light_visible(t_vector cam_pos, t_vector light_pos,
					t_object obj);
bool			in_shadow(t_ray light_ray, t_data *data, t_light light);
//	shadows/calculate_normals.c
t_point			calculate_normal(t_vector view_direction,
					t_ray light_ray, t_object obj);
//	shadows/diffuse.c
t_rgb			diffuse_specular_falloff(t_light light, t_ray light_ray,
					t_ray view_ray, t_object obj);
t_rgb			calculate_ambient(t_object obj, t_ambient ambient);

//	utils/ray_utils.c
t_ray			get_ray_for_px(t_data *data, int px, int py);
t_point			get_point(t_ray ray, float t);
t_ray			build_light_ray(t_ray ray, float t, t_light light,
					bool near_plane);
//	utils/main_utils.c
void			setup_rendering(t_data *data);

// vector_utils/vector.c && vector_2.c
t_vector		vector(float x, float y, float z);
t_vector		vector_add(t_vector a, t_vector b);
t_vector		vector_cross(t_vector a, t_vector b);
t_vector		vector_subtract(t_vector a, t_vector b);
t_vector		vector_multiply(t_vector a, float scalar);
float			vector_dot(t_vector a, t_vector b);
float			vector_magnitude(t_vector a);
void			vector_normalize(t_vector *a);
t_vector		rotate_vector(t_vector v, t_vector a, float angle);

//	debug/debug.c
void			print_cam_info(t_data data);
//	main.c
void			cleanup_data(t_data *data);
void			init_data(t_data *data);

#endif
