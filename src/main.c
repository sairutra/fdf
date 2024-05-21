/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:43:03 by spenning          #+#    #+#             */
/*   Updated: 2024/05/21 10:02:17 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float fraction(float x1, float x2, float x)
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
	if	(abs(dx) > abs(dy))
		fract = fraction(a->ox, b->ox, a->x);
	else
		fract = fraction(a->oy, b->oy, a->y);
	return fract;
}

int	cal_color (t_point *a, t_point *b)
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

void slope_less_then_one(t_data *data, t_dxy *d, t_point *a, t_point *b)
{
	int p;
	int i;

	(void)b;
	i = -1;
	p = 2 * abs(d->dy) - abs(d->dx);
	// ft_printf("lp %d\n", p);
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
		// ft_printf("lp %d\n", p);
		pixel_put(data, a->x, a->y, cal_color(a, b));
	}
}

void slope_bigger_then_one(t_data *data, t_dxy *d, t_point *a, t_point *b)
{
	int p;
	int i;

	(void)b;
	i = -1;
	p = 2 * abs(d->dx) - abs(d->dy);
	// ft_printf("bp %d\n", p);
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
		// ft_printf("bp %d\n", p);
		pixel_put(data, a->x, a->y, cal_color(a, b));
	}
}

void calculate_slope(t_data *data, t_point *a, t_point *b)
{
	t_dxy d;
	
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
	// ft_printf("dx %d\n", dx);
	// ft_printf("dy %d\n", dy);
}


void	rotate_z(t_point *a, t_point *b, int gamma)
{
	int	tmp;

	tmp = a->z;
	a->x = tmp * cos(gamma) - a->y * sin(gamma);
	a->y = tmp * sin(gamma) + a->y * cos(gamma);
	tmp = b->z;
	b->x = tmp * cos(gamma) - b->y * sin(gamma);
	b->y = tmp * sin(gamma) + b->y * cos(gamma);
}

void	rotate_y(t_point *a, t_point *b, int tetha)
{
	int	tmp;

	tmp = a->x;
	a->x = tmp * cos(tetha) + a->z * sin(tetha);
	a->z = a->z * cos(tetha) - tmp * sin(tetha);
	tmp = b->x;
	b->x = tmp * cos(tetha) + b->z * sin(tetha);
	b->z = b->z * cos(tetha) - tmp * sin(tetha);
}

void	rotate_x(t_point *a, t_point *b, int alpha)
{
	int	tmp;

	tmp = a->y;
	a->y = tmp * cos(alpha) - a->z * sin(alpha);
	a->z = tmp * sin(alpha) + a->z * cos(alpha);
	tmp = b->y;
	b->y = tmp * cos(alpha) - b->z * sin(alpha);
	b->z = tmp * sin(alpha) + b->z * cos(alpha);
}


void	isometric(t_point *a, t_point *b)
{
	int tmp;

	// ft_printf("z %d\n", z);
	tmp = a->x;
	a->x = (tmp - a->y) * cos(0.523599);
	a->y = (tmp + a->y) * sin(0.523599) - a->z;
	tmp = b->x;
	b->x = (tmp - b->y) * cos(0.523599);
	b->y = (tmp + b->y) * sin(0.523599) - b->z;
}



void draw_line(t_data *data, t_point *a, t_point *b)
{
	int zoom = (WIDTH / data->columns / (2 * (WIDTH / HEIGHT)));

	a->x *= zoom;
	b->x *= zoom;
	a->y *= zoom;
	b->y *= zoom;
	a->z *= zoom;
	b->z *= zoom;
	// rotate_x(a, b, 0);
	// rotate_y(a, b, 0);
	// rotate_z(a, b, 0);
	isometric(a, b);
	// printf("b->y %d\n", b->y);
	a->x += WIDTH / 2;
	b->x += WIDTH / 2;
	a->y += HEIGHT / 3;
	b->y += HEIGHT / 3;
	// printf("b->y %d\n", b->y);

	// printf("zoom width height a->x a->y b->x b->y %d %d %d %d %d %d %d\n", zoom, data->width, data->height ,a->x, a->y, b->x, b->y);
	calculate_slope(data, a, b);
}

t_point *ip(t_point *point, t_data *data, int x, int y)
{
	point->x = x;
	point->y = y;
	point->z = data->map[x][y];
	point->color = data->map_color[x][y];
	return (point);
}

void draw_map(t_data *data)
{
	int		x;
	int		y; 
	t_point	a;
	t_point b;

	x = 0;
	while (x < data->rows)
	{
		y = 0;
		// ft_printf("x %d\n", x);
		while (y < data->columns)
		{
			// ft_printf("y %d\n", y);
			if (x < data->rows - 1)
				draw_line(data, ip(&a, data, x, y), ip(&b, data, x + 1, y));
			if (y < data->columns - 1)
				draw_line(data, ip(&a, data, x, y), ip(&b, data, x, y + 1));
			y++;
		}
		x++;
	}
}


int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
		parse(argv, &data);
	else
		return (EXIT_FAILURE);
	data_init(&data);
	draw_map(&data);
	// calculate_slope(&data);
	// draw_squares(&data, data.width, data.height, rev_color(color));
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	hooks(&data);
	mlx_loop(data.mlx);
}
