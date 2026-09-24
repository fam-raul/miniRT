/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/24 15:24:13 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	render_pixels(t_app *app)
{
	int		x;
	int		y;
	t_ray	ray;
	t_hit	hit;
	t_color	c;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray = create_camera_ray(&app->scene.camera, x, y);
			if (hit_scene(&app->scene, &ray, &hit))
				c = shade_hit(&app->scene, &hit);
			else
				c = color3(0.0, 0.0, 0.0);
			img_put_pixel(&app->img, x, y, color_to_int(c));
			x++;
		}
		y++;
	}
}

void	render_scene(t_app *app)
{
	build_camera_basis(&app->scene.camera);
	render_pixels(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img.ptr, 0, 0);
}
