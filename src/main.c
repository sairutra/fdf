/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:43:03 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 23:13:03 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void slope_less_then_one(t_data *data, int dx, int dy, int ax, int ay)
{
	int p;
	int i;

	i = -1;
	p = 2 * abs(dy) - abs(dx);
	// ft_printf("lp %d\n", p);
	while (++i < abs(dx))
	{
		if (dx > 0)
			ax += 1;
		else
			ax -= 1;
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			if (dy > 0)
				ay += 1;
			else
				ay -= 1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		// ft_printf("lp %d\n", p);
		pixel_put(data, ax, ay, trgb(0, 255, 255, 255));
	}
}

void slope_bigger_then_one(t_data *data, int dx, int dy, int ax, int ay)
{
	int p;
	int i;

	i = -1;
	p = 2 * abs(dx) - abs(dy);
	// ft_printf("bp %d\n", p);
	while (++i < abs(dy))
	{
		if (dy > 0)
			ay += 1;
		else
			ay -= 1;
		if (p < 0)
			p = p + 2 * abs(dx);
		else
		{
			if (dx > 0)
				ax += 1;
			else
				ax -= 1;
			p = p + 2 * abs(dx) - 2 * abs(dy);
		}
		// ft_printf("bp %d\n", p);
		pixel_put(data, ax, ay, trgb(0, 255, 255, 255));
	}
}

void calculate_slope(t_data *data, int ax, int ay, int bx, int by)
{
	int dx;
	int dy;

	
	dx = bx - ax;
	dy = by - ay;

	if (abs(dx) > abs(dy))
		slope_less_then_one(data, dx, dy, ax, ay);
	else
		slope_bigger_then_one(data, dx, dy, ax, ay);
	// ft_printf("dx %d\n", dx);
	// ft_printf("dy %d\n", dy);
}


void	rotate_z(int *x, int *y, int *z, int gamma)
{
	int	tmp;

	tmp = *z;
	*x = tmp * cos(gamma) - *y * sin(gamma);
	*y = tmp * sin(gamma) + *y * cos(gamma);
}

void	rotate_y(int *x, int *z, int tetha)
{
	int	tmp;

	tmp = *x;
	*x = tmp * cos(tetha) + *z * sin(tetha);
	*z = *z * cos(tetha) - tmp * sin(tetha);
}

void	rotate_x(int *y, int *z, int alpha)
{
	int	tmp;

	tmp = *y;
	*y = tmp * cos(alpha) - *z * sin(alpha);
	*z = tmp * sin(alpha) + *z * cos(alpha);
}


void	isometric(int *x, int *y, int z)
{
	int tmp;

	// ft_printf("z %d\n", z);
	tmp = *x;
	*x = (tmp - *y) * cos(0.523599);
	*y = (tmp + *y) * sin(0.523599) - z;
}

void draw_line(t_data *data, int ax, int ay, int bx, int by)
{
	// int zoom = (WIDTH / data->columns) / 3;
	int zoom = (HEIGHT / data->rows) / 3;
	int az;
	int bz;

	az = data->map[ax][ay];
	bz = data->map[bx][by];
	ax *= zoom;
	bx *= zoom;
	ay *= zoom;
	by *= zoom;
	az *= zoom;
	bz *= zoom;
	// rotate_x(&ay, &az, 0);
	// rotate_y(&ax, &az, 0);
	// rotate_z(&ax, &ay, &az, 0);
	// rotate_x(&by, &bz, 0);
	// rotate_y(&bx, &bz, 0);
	// rotate_z(&bx, &by, &bz, 0);
	isometric(&ax, &ay, az);
	isometric(&bx, &by, bz);
	// printf("by %d\n", by);
	ax += 300 + (WIDTH - 300) / 2;
	bx += 300 + (WIDTH - 300) / 2;
	ay += data->height / 2;
	by += data->height / 2;
	// printf("by %d\n", by);

	// printf("zoom width height ax ay bx by %d %d %d %d %d %d %d\n", zoom, data->width, data->height ,ax, ay, bx, by);
	calculate_slope(data, ax, ay, bx, by);
}

void draw_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->rows)
	{
		y = 0;
		// ft_printf("x %d\n", x);
		while (y < data->columns)
		{
			// ft_printf("y %d\n", y);
			if (x < data->rows - 1)
				draw_line(data, x, y, x + 1, y);
			if (y < data->columns - 1)
				draw_line(data, x, y, x, y + 1);
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
