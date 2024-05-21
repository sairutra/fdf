/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:10:59 by mynodeus          #+#    #+#             */
/*   Updated: 2024/05/21 10:27:43 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

// rotate_x(a, b, 0);
// rotate_y(a, b, 0);
// rotate_z(a, b, 0);
// ft_debug("zoom width height a->x a->y b->x b->y %d %d %d %d %d %d %d\n"
//, zoom, data->width, data->height ,a->x, a->y, b->x, b->y);
void	draw_line(t_data *data, t_point *a, t_point *b)
{
	int	zoom;

	zoom = (WIDTH / data->columns / (2 * (WIDTH / HEIGHT)));
	a->x *= zoom;
	b->x *= zoom;
	a->y *= zoom;
	b->y *= zoom;
	a->z *= zoom;
	b->z *= zoom;
	isometric(a, b);
	a->x += WIDTH / 2;
	b->x += WIDTH / 2;
	a->y += HEIGHT / 3;
	b->y += HEIGHT / 3;
	calculate_slope(data, a, b);
}

t_point	*ip(t_point *point, t_data *data, int x, int y)
{
	point->x = x;
	point->y = y;
	point->z = data->map[x][y];
	point->color = data->map_color[x][y];
	return (point);
}

void	draw_map(t_data *data)
{
	int		x;
	int		y;
	t_point	a;
	t_point	b;

	x = 0;
	while (x < data->rows)
	{
		y = 0;
		while (y < data->columns)
		{
			if (x < data->rows - 1)
				draw_line(data, ip(&a, data, x, y), ip(&b, data, x + 1, y));
			if (y < data->columns - 1)
				draw_line(data, ip(&a, data, x, y), ip(&b, data, x, y + 1));
			y++;
		}
		x++;
	}
}
