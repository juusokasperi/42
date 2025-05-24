/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:18:26 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/22 10:39:49 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_rgb	calculate_diffuse(t_light light, t_ray light_ray, t_object obj,
					t_point surface_normal);
static t_rgb	calculate_specular(t_light light, t_ray light_ray,
					t_ray view_ray, t_point surface_normal);
static t_rgb	calculate_falloff(t_rgb color, t_ray light_ray, t_light light);

/*
	@return the diffuse, specular and falloff added together.
*/
t_rgb	diffuse_specular_falloff(t_light light, t_ray light_ray,
	t_ray view_ray, t_object obj)
{
	t_point	surface_normal;
	t_rgb	diffuse;
	t_rgb	specular;
	t_rgb	res;

	surface_normal = calculate_normal(view_ray.direction, light_ray, obj);
	if (vector_dot(surface_normal, light_ray.direction) < EPSILON)
		return ((t_rgb){0, 0, 0});
	diffuse = calculate_diffuse(light, light_ray, obj, surface_normal);
	specular = calculate_specular(light, light_ray, view_ray, surface_normal);
	diffuse = calculate_falloff(diffuse, light_ray, light);
	specular = calculate_falloff(specular, light_ray, light);
	res = rgb_add(diffuse, specular);
	return (res);
}

/*
Calculates the color that is present always whether the object is in
shadow or not.
*/
t_rgb	calculate_ambient(t_object obj, t_ambient ambient)
{
	t_rgb	res;

	res = rgb_scalar_multiply(obj.color, ambient.ratio);
	res = rgb_scalar(res, ambient.color);
	return (res);
}

/*
	1. Makes sure the normal faces towards the light.
	2. Calculate brightness based on the angle the light hits the object;
		If light hits object straight (90 degress), maximum
		If hits at an angle, reduced brigtness
	3. Calculate the light color and intensity to light_contribution
	@return object color * light color * diffuse factor.
*/
static t_rgb	calculate_diffuse(t_light light, t_ray light_ray, t_object obj,
	t_point surface_normal)
{
	float	diffuse_factor;
	t_rgb	diffuse_color;
	t_rgb	light_contribution;

	if (vector_dot(light_ray.direction, surface_normal) < 0)
		surface_normal = vector_multiply(surface_normal, -1.0f);
	diffuse_factor = fmaxf(0.0f,
			vector_dot(surface_normal, light_ray.direction));
	light_contribution = rgb_scalar_multiply(light.color, light.ratio);
	diffuse_color = rgb_scalar_multiply(obj.color, diffuse_factor);
	diffuse_color = rgb_scalar(diffuse_color, light_contribution);
	return (diffuse_color);
}

/*
	1. Calculate the dot product of normal and light_ray direction
		and creates the normalized reflection vector
	2. Flips the view direction to point from surface to camera
	3. Calculate the highlight intensity based on how close we are looking
		at the reflection. The power controls how tight the highlight is.
	4. Apply the shininess factor (divided by half to reduce the intensity)
		to the color.
*/
static t_rgb	calculate_specular(t_light light, t_ray light_ray,
	t_ray view_ray, t_point surface_normal)
{
	t_vector	reflection;
	float		factor;
	float		n_dot_l;

	n_dot_l = vector_dot(surface_normal, light_ray.direction);
	reflection = vector_subtract(vector_multiply(
				surface_normal, 2.0f * n_dot_l), light_ray.direction);
	vector_normalize(&reflection);
	view_ray.direction = vector_multiply(view_ray.direction, -1.0f);
	factor = powf(fmaxf(0.0f, vector_dot(reflection, view_ray.direction)), 32);
	return (rgb_scalar_multiply(light.color, factor * 0.5f));
}

/*
	Light gets weaker the farther it is from the hit point.
*/
static t_rgb	calculate_falloff(t_rgb color, t_ray light_ray, t_light light)
{
	float	dist;
	float	attenuation;

	dist = vector_magnitude(vector_subtract(light.pos, light_ray.origin));
	attenuation = 1.0f / (1.0f + 0.001f * dist + 0.0001f * dist * dist);
	return (rgb_scalar_multiply(color, attenuation));
}
