/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 20:50:25 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Builds a color container in RGB space. */
t_color	color3(double r, double g, double b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

/* Multiplies each channel by a scalar. */
t_color	color_scale(t_color c, double s)
{
	return (color3(c.r * s, c.g * s, c.b * s));
}

/* Multiplies two colors channel by channel. */
t_color	color_mul(t_color a, t_color b)
{
	return (color3(a.r * b.r, a.g * b.g, a.b * b.b));
}

/* Converts floating RGB channels to 0xRRGGBB integer. */
int	color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = (int)round(clamp_value(c.r, 0.0, 255.0));
	g = (int)round(clamp_value(c.g, 0.0, 255.0));
	b = (int)round(clamp_value(c.b, 0.0, 255.0));
	return ((r << 16) | (g << 8) | b);
}

/* Writes one pixel in the mlx image buffer. */
void	img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}
