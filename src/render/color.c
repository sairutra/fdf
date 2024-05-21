/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:13:25 by mynodeus          #+#    #+#             */
/*   Updated: 2024/05/21 10:30:18 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

float	fraction(float x1, float x2, float x)
{
	if (x1 != x2)
		return ((x - x1) / (x2 - x1));
	return (0);
}

float	cfraction(t_point *a, t_point *b)
{
	int		dx;
	int		dy;
	float	fract;

	dx = b->ox - a->ox;
	dy = b->oy - a->oy;
	if (abs(dx) > abs(dy))
		fract = fraction(a->ox, b->ox, a->x);
	else
		fract = fraction(a->oy, b->oy, a->y);
	return (fract);
}

int	cal_color(t_point *a, t_point *b)
{
	float	fract;
	int		r;
	int		g;
	int		bl;

	fract = cfraction(a, b);
	r = get_r(a->color) + (get_r(b->color) - get_r(a->color)) * fract;
	g = get_g(a->color) + (get_g(b->color) - get_g(a->color)) * fract;
	bl = get_b(a->color) + (get_b(b->color) - get_b(a->color)) * fract;
	return (trgb(0, r, g, bl));
}
