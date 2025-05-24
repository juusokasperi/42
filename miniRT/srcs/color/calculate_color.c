/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:23:55 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/19 23:45:28 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static float	calculate_threshold(t_object obj, float cam_dist);
static bool		check_nearby_planes(t_object obj,
					t_data *data, t_point hit_point);

/*
	@return	t_rgb struct for mlx_put_pixel.
*/
t_rgb	calculate_color(t_data *data, t_object obj, t_ray ray, float t)
{
	t_calc_context	ctx;
	bool			near_pl;
	int				i;

	ctx.hit_point = get_point(ray, t);
	check_checkerboard(&obj, ctx.hit_point);
	ctx.final_color = calculate_ambient(obj, data->ambient);
	near_pl = check_nearby_planes(obj, data, ctx.hit_point);
	i = -1;
	while (++i < data->scene.light_count)
	{
		ctx.light_ray = build_light_ray(ray, t, data->scene.lights[i], near_pl);
		if (!light_visible(data->cam.pos, data->scene.lights[i].pos, obj))
			continue ;
		if (!in_shadow(ctx.light_ray, data, data->scene.lights[i]))
		{
			ctx.diffuse = diffuse_specular_falloff(data->scene.lights[i],
					ctx.light_ray, ray, obj);
			ctx.final_color = rgb_add(ctx.final_color, ctx.diffuse);
		}
	}
	return (ctx.final_color);
}

/*
	Checks whether the intersection is close to a plane and returns true
	in that case. This boolean is used to decide whether to use a smaller
	or larger offset when building the ray from our intersection hit point and
	the light source.
*/
static bool	check_nearby_planes(t_object obj, t_data *data, t_point hit_point)
{
	int		i;
	float	dist_to_plane;
	float	threshold;
	float	cam_dist;

	cam_dist = vector_magnitude(vector_subtract(hit_point, data->cam.pos));
	if (cam_dist > 20.0f)
		return (false);
	threshold = calculate_threshold(obj, cam_dist);
	i = -1;
	while (++i < data->scene.object_count)
	{
		if (data->scene.objects[i].type == PLANE
			&& &data->scene.objects[i] != &obj)
		{
			dist_to_plane = fabsf(
					vector_dot(vector_subtract(hit_point,
							data->scene.objects[i].data.plane.point),
						data->scene.objects[i].data.plane.normal));
			if (dist_to_plane < threshold)
				return (true);
		}
	}
	return (false);
}

/*
	Calculates a threshold for the distance_to_plane calculation
	based on object radius and distance from hit point to camera.
*/
static float	calculate_threshold(t_object obj, float cam_dist)
{
	float	obj_size;

	if (obj.type == SPHERE)
		obj_size = obj.data.sphere.radius;
	else if (obj.type == CYLINDER || obj.type == CONE)
		obj_size = obj.data.cylinder.radius;
	else
		obj_size = 1.0f;
	return (fminf(0.01f, obj_size * 0.01f + cam_dist / 1000.0f));
}

void	fill_black(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
			mlx_put_pixel(data->mlx_img, x, y, 0x000000FF);
	}
}
