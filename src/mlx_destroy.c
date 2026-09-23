/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 20:49:07 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

#ifdef __linux__
/* Releases mlx display internals and the mlx context on linux. */
void	destroy_display(void *mlx)
{
	mlx_destroy_display(mlx);
	free(mlx);
}
#else

/* Keeps API symmetry on non-linux builds. */
void	destroy_display(void *mlx)
{
	(void)mlx;
}
#endif
