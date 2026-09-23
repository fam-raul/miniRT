/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 21:07:42 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Adds two colors channel-wise. */
static t_color	add_color(t_color a, t_color b)
{
	return (color3(a.r + b.r, a.g + b.g, a.b + b.b));
}

/* Computes ambient lighting term for one hit point. */
static t_color	ambient_term(const t_scene *scene, const t_hit *hit)
{
	t_color	ambient_tint;
	t_color	base;

	ambient_tint = color_scale(scene->ambient.color, 1.0 / 255.0);
	base = color_mul(hit->color, ambient_tint);
	return (color_scale(base, scene->ambient.ratio));
}

/* Casts one shadow ray toward the light and checks any blocker. */
int	is_in_shadow(const t_scene *scene, const t_hit *hit)
{
	t_ray	shadow;
	t_vec3	to_light;
	double	dist;

	to_light = vec_sub(scene->light.pos, hit->point);
	dist = vec_length(to_light);
	shadow.origin = vec_add(hit->point, vec_scale(hit->normal, SHADOW_BIAS));
	shadow.dir = vec_normalize(to_light);
	return (hit_shadow(scene, &shadow, dist - SHADOW_BIAS));
}

t_color	shade_hit(const t_scene *scene, const t_hit *hit)
{
	t_color	out;
	t_color	diffuse;
	t_vec3	light_dir;
	double	n_dot_l;

	out = ambient_term(scene, hit);
	if (is_in_shadow(scene, hit))
		return (out);
	light_dir = vec_normalize(vec_sub(scene->light.pos, hit->point));
	n_dot_l = fmax(0.0, vec_dot(hit->normal, light_dir));
	diffuse = color_scale(hit->color, scene->light.ratio * n_dot_l);
	return (add_color(out, diffuse));
}
