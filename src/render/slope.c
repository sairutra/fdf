/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slope.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:12:43 by mynodeus          #+#    #+#             */
/*   Updated: 2024/05/21 10:29:04 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void	slope_less_then_one(t_data *data, t_dxy *d, t_point *a, t_point *b)
{
	int	p;
	int	i;

	i = -1;
	p = 2 * abs(d->dy) - abs(d->dx);
	ft_debug("lp %d\n", p);
	while (++i < abs(d->dx))
	{
		if (d->dx > 0)
			a->x += 1;
		else
			a->x -= 1;
		if (p < 0)
			p = p + 2 * abs(d->dy);
		else
		{
			if (d->dy > 0)
				a->y += 1;
			else
				a->y -= 1;
			p = p + 2 * abs(d->dy) - 2 * abs(d->dx);
		}
		ft_debug("lp %d\n", p);
		pixel_put(data, a->x, a->y, cal_color(a, b));
	}
}

void	slope_bigger_then_one(t_data *data, t_dxy *d, t_point *a, t_point *b)
{
	int	p;
	int	i;

	i = -1;
	p = 2 * abs(d->dx) - abs(d->dy);
	ft_debug("bp %d\n", p);
	while (++i < abs(d->dy))
	{
		if (d->dy > 0)
			a->y += 1;
		else
			a->y -= 1;
		if (p < 0)
			p = p + 2 * abs(d->dx);
		else
		{
			if (d->dx > 0)
				a->x += 1;
			else
				a->x -= 1;
			p = p + 2 * abs(d->dx) - 2 * abs(d->dy);
		}
		ft_debug("bp %d\n", p);
		pixel_put(data, a->x, a->y, cal_color(a, b));
	}
}

void	calculate_slope(t_data *data, t_point *a, t_point *b)
{
	t_dxy	d;

	d.dx = b->x - a->x;
	d.dy = b->y - a->y;
	a->ox = a->x;
	a->oy = a->y;
	b->ox = b->x;
	b->oy = b->y;
	if (abs(d.dx) > abs(d.dy))
		slope_less_then_one(data, &d, a, b);
	else
		slope_bigger_then_one(data, &d, a, b);
}
