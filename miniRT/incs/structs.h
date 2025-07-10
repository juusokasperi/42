/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:13:36 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/22 11:57:10 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42/MLX42.h"

typedef enum e_shape
{
	NONE = -1,
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_shape;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vector;

typedef struct s_interval
{
	float	min;
	float	max;
}	t_interval;

typedef struct s_aabb_bounds
{
	t_vector	min;
	t_vector	max;
}	t_aabb_bounds;

typedef struct s_bvh_node
{
	t_aabb_bounds	bounds;
	uint32_t		left_right;
	uint32_t		first_count;
}	t_bvh_node;

typedef struct s_bvh
{
	t_bvh_node	*nodes;
	uint32_t	node_count;
}	t_bvh;

typedef struct s_vector		t_point;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_viewport
{
	float		width;
	float		height;
	int			fov;
	float		distance;
}	t_viewport;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
	t_viewport	vp;
}	t_camera;

typedef struct s_cam_controls
{
	float	move_speed;
	float	rotate_speed;
}	t_cam_controls;

typedef struct s_ambient
{
	t_rgb	color;
	float	ratio;
}	t_ambient;

typedef struct s_light
{
	t_rgb		color;
	t_vector	pos;
	float		ratio;
}	t_light;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_checkerboard
{
	t_rgb	color_1;
	t_rgb	color_2;
	float	scale;
}	t_checkerboard;

typedef struct s_sphere
{
	t_point	center;
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_point		point;
	t_vector	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	axis;
	float		radius;
	float		height;
	t_point		local_hit;
}	t_cylinder;

typedef struct s_cylinder	t_cone;

typedef struct s_object
{
	t_shape			type;
	t_rgb			color;
	bool			is_checkered;
	t_checkerboard	checkerboard;
	union u_data
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
	}	data;
}	t_object;

typedef struct s_scene
{
	t_object	*objects;
	int			object_count;
	t_light		*lights;
	int			light_count;
}	t_scene;

typedef struct s_data
{
	t_camera		cam;
	t_ambient		ambient;
	mlx_t			*mlx_ptr;
	mlx_image_t		*mlx_img;
	t_scene			scene;
	t_bvh			bvh;
	t_cam_controls	cam_controls;
	int				thread_count;
	int				width;
	int				height;
	bool			should_update;
	int				camera_count;
	int				ambient_count;
}	t_data;

typedef struct s_obj_t
{
	float		min_t;
	t_object	*closest;
	t_object	*objects;
}	t_obj_t;

typedef struct s_calc_context
{
	t_rgb	diffuse;
	t_rgb	final_color;
	t_ray	light_ray;
	t_point	hit_point;
}	t_calc_context;

#endif
