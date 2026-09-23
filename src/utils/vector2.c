/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 20:49:47 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Computes the cross product between two vectors. */
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (vec3(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

/* Returns the euclidean length of a vector. */
double	vec_length(t_vec3 v)
{
	return (sqrt(vec_dot(v, v)));
}

/* Normalizes a vector and returns zero-vector when tiny. */
t_vec3	vec_normalize(t_vec3 v)
{
	double	len;

	len = vec_length(v);
	if (len < EPSILON)
		return (vec3(0.0, 0.0, 0.0));
	return (vec_scale(v, 1.0 / len));
}

/* Clamps a value to the inclusive [min, max] range. */
double	clamp_value(double v, double min, double max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

/* Gets a point located at ray.origin + ray.dir * t. */
t_vec3	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.dir, t)));
}
