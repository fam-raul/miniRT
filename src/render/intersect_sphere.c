/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 20:51:04 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Intersects a ray with a sphere and returns nearest positive t. */
int	intersect_sphere(const t_ray *ray, const t_object *obj, double *t)
{
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	disc;

	oc = vec_sub(ray->origin, obj->sphere.center);
	a = vec_dot(ray->dir, ray->dir);
	half_b = vec_dot(oc, ray->dir);
	c = vec_dot(oc, oc) - obj->sphere.radius * obj->sphere.radius;
	disc = half_b * half_b - a * c;
	if (disc < 0.0)
		return (0);
	*t = (-half_b - sqrt(disc)) / a;
	if (*t > EPSILON)
		return (1);
	*t = (-half_b + sqrt(disc)) / a;
	return (*t > EPSILON);
}
