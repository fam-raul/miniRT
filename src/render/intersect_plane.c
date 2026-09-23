/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 20:51:07 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Intersects a ray with an infinite plane and returns positive t. */
int	intersect_plane(const t_ray *ray, const t_object *obj, double *t)
{
	double	denom;
	double	numer;

	denom = vec_dot(obj->plane.normal, ray->dir);
	if (fabs(denom) < EPSILON)
		return (0);
	numer = vec_dot(vec_sub(obj->plane.point, ray->origin), obj->plane.normal);
	*t = numer / denom;
	return (*t > EPSILON);
}
