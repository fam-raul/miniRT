/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/23 21:00:16 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Parses and consumes an optional sign character. */
static int	read_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

/* Reads an unsigned integer part as double and reports digit presence. */
static int	read_intpart(const char *s, int *i, double *val)
{
	int	digits;

	digits = 0;
	*val = 0.0;
	while (ft_isdigit(s[*i]))
	{
		*val = *val * 10.0 + (s[*i] - '0');
		(*i)++;
		digits = 1;
	}
	return (digits);
}

/* Reads optional fraction part and returns whether it had digits. */
static int	read_fraction(const char *s, int *i, double *frac)
{
	double	num;
	double	den;
	int		digits;

	num = 0.0;
	den = 1.0;
	digits = 0;
	*frac = 0.0;
	if (s[*i] != '.')
		return (0);
	(*i)++;
	while (ft_isdigit(s[*i]))
	{
		num = num * 10.0 + (s[*i] - '0');
		den *= 10.0;
		(*i)++;
		digits = 1;
	}
	*frac = num / den;
	return (digits);
}

/* Parses a decimal string into double without exponent syntax. */
int	parse_double(const char *s, double *out)
{
	int		i;
	int		sign;
	int		digits;
	double	intpart;
	double	frac;

	if (!s || !s[0])
		return (1);
	i = 0;
	sign = read_sign(s, &i);
	digits = read_intpart(s, &i, &intpart);
	digits += read_fraction(s, &i, &frac);
	if (!digits || s[i] != '\0')
		return (1);
	*out = (intpart + frac) * sign;
	return (0);
}
