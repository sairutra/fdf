/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:11:55 by mynodeus          #+#    #+#             */
/*   Updated: 2024/05/21 14:01:47 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

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

// https://www.youtube.com/watch?v=cgPYLJ-s5II
// https://www.youtube.com/watch?v=04oQ2jOUjkU
void	isometric(t_point *a, t_point *b)
{
	int	tmpx;
	int	tmpy;

	tmpx = a->x;
	tmpy = a->y;
	a->x = tmpx * 1 + tmpy * -1;
	a->y = tmpx * 0.5 + tmpy * 0.5 - a->z;
	tmpx = b->x;
	tmpy = b->y;
	b->x = tmpx * 1 + tmpy * -1;
	b->y = tmpx * 0.5 + tmpy * 0.5 - b->z;
}
