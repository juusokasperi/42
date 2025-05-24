/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:52:33 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/14 18:12:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	vector_magnitude(t_vector a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

void	vector_normalize(t_vector *a)
{
	float		magnitude;

	magnitude = vector_magnitude(*a);
	if (magnitude == 0)
	{
		a->x = 0;
		a->y = 0;
		a->z = 0;
	}
	else
	{
		a->x /= magnitude;
		a->y /= magnitude;
		a->z /= magnitude;
	}
}

t_vector	rotate_vector(t_vector v, t_vector a, float angle)
{
	t_vector	res;
	t_vector	cross;
	float		cos_a;
	float		sin_a;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	res = vector_multiply(v, cos_a);
	cross = vector_cross(a, v);
	cross = vector_multiply(cross, sin_a);
	res = vector_add(res, cross);
	a = vector_multiply(a, vector_dot(a, v) * (1 - cos_a));
	res = vector_add(res, a);
	return (res);
}
