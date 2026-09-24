/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/24 15:19:43 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	close_window(t_app *app)
{
	destroy_app(app, 0);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_app *app)
{
	if (keycode == KEY_ESC_LINUX)
		return (close_window(app));
	return (0);
}

int	expose_hook(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->win, app->img.ptr, 0, 0);
	return (0);
}

int	loop_hook(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->win, app->img.ptr, 0, 0);
	return (0);
}
