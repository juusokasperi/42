/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_aabb_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:11:01 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/22 16:58:34 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
	@return Boolean stating whether the ray intersect the AABB.
*/
bool	ray_aabb_intersect(t_ray ray, t_aabb_bounds bounds,
	float *t_min, float *t_max)
{
	t_aabb_bounds	bounds_store;

	if (!check_axis_bounds(
			ray.origin.x, ray.direction.x, bounds.min.x, bounds.max.x)
		|| !check_axis_bounds(
			ray.origin.y, ray.direction.y, bounds.min.y, bounds.max.y)
		|| !check_axis_bounds(
			ray.origin.z, ray.direction.z, bounds.min.z, bounds.max.z))
		return (false);
	bounds_store = calc_axis_intervals(ray, bounds);
	*t_min = fmaxf(bounds_store.min.x,
			fmaxf(bounds_store.min.y, bounds_store.min.z));
	*t_max = fminf(bounds_store.max.x,
			fminf(bounds_store.max.y, bounds_store.max.z));
	return (*t_max > *t_min && *t_max > 0);
}

/*
	Checks if the ray's direction along an axis is nearly zero,
	in which case an intersection is possible only if the
	ray's origin is between the min/max bounds on the axis.
*/
bool	check_axis_bounds(float origin, float direction,
	float min, float max)
{
	if (fabsf(direction) < EPSILON)
		if (origin < min || origin > max)
			return (false);
	return (true);
}

/*
	Calculates where a ray enter and exits a space between two
	parallel planes for a single axis.

	In case the axis moves parallel to the planes, min and max values for
	said axis will be set to i and FLT_MAX so they are non-constraining
	in the later intersection calculation.

	@return t_interval, which contains two parameters;
		res.min: when the ray first enters a plane along the axis
		res.max: when the ray exits through the second plane
*/
t_interval	calc_single_axis(float origin, float dir,
		float min, float max)
{
	t_interval	res;
	float		tmp;

	if (fabsf(dir) < EPSILON)
	{
		res.min = 0;
		res.max = FLT_MAX;
	}
	else
	{
		res.min = (min - origin) / dir;
		res.max = (max - origin) / dir;
		if (res.min > res.max)
		{
			tmp = res.min;
			res.min = res.max;
			res.max = tmp;
		}
	}
	return (res);
}

/*
	@return t_aabb_bounds struct containing the entry and exit points
			for each axis between two parallel planes.
*/
t_aabb_bounds	calc_axis_intervals(t_ray ray, t_aabb_bounds bounds)
{
	t_aabb_bounds	res;
	t_interval		x;
	t_interval		y;
	t_interval		z;

	x = calc_single_axis(ray.origin.x, ray.direction.x,
			bounds.min.x, bounds.max.x);
	y = calc_single_axis(ray.origin.y, ray.direction.y,
			bounds.min.y, bounds.max.y);
	z = calc_single_axis(ray.origin.z, ray.direction.z,
			bounds.min.z, bounds.max.z);
	res.min.x = x.min;
	res.max.x = x.max;
	res.min.y = y.min;
	res.max.y = y.max;
	res.min.z = z.min;
	res.max.z = z.max;
	return (res);
}
