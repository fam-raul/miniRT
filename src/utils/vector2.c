/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/24 15:34:19 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	return (vec3(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

double	vec_length(t_vec3 v)
{
	return (sqrt(vec_dot(v, v)));
}

t_vec3	vec_normalize(t_vec3 v)
{
	double	len;

	len = vec_length(v);
	if (len < EPSILON)
		return (vec3(0.0, 0.0, 0.0));
	return (vec_scale(v, 1.0 / len));
}

double	clamp_value(double v, double min, double max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

t_vec3	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.dir, t)));
}
