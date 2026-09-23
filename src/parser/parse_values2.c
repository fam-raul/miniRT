/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 20:51:23 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Parses FOV degrees in the inclusive [0, 180] interval. */
int	parse_fov(const char *s, double *out)
{
	if (parse_double(s, out))
		return (1);
	if (*out < 0.0 || *out > 180.0)
		return (1);
	return (0);
}
