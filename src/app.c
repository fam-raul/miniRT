/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 20:49:37 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* Initializes the runtime container with zeroed fields. */
void	init_app(t_app *app)
{
	app->mlx = NULL;
	app->win = NULL;
	app->img.ptr = NULL;
	app->img.addr = NULL;
	app->img.bpp = 0;
	app->img.line_len = 0;
	app->img.endian = 0;
	app->scene.objects = NULL;
	app->scene.obj_count = 0;
	app->scene.obj_cap = 0;
	app->scene.has_ambient = 0;
	app->scene.has_camera = 0;
	app->scene.has_light = 0;
}

/* Releases dynamic scene allocations. */
void	free_scene(t_scene *scene)
{
	free(scene->objects);
	scene->objects = NULL;
	scene->obj_count = 0;
	scene->obj_cap = 0;
}

/* Destroys allocated resources and exits with status. */
int	destroy_app(t_app *app, int status)
{
	if (app->img.ptr && app->mlx)
		mlx_destroy_image(app->mlx, app->img.ptr);
	if (app->win && app->mlx)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
		destroy_display(app->mlx);
	free_scene(&app->scene);
	return (status);
}

/* Creates mlx context, window and the framebuffer image. */
int	init_mlx(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (rt_error("mlx_init failed", -1));
	app->win = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!app->win)
		return (rt_error("mlx_new_window failed", -1));
	app->img.ptr = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!app->img.ptr)
		return (rt_error("mlx_new_image failed", -1));
	app->img.addr = mlx_get_data_addr(app->img.ptr, &app->img.bpp,
			&app->img.line_len, &app->img.endian);
	if (!app->img.addr)
		return (rt_error("mlx_get_data_addr failed", -1));
	return (0);
}
