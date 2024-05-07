/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opposite_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:23:31 by spenning          #+#    #+#             */
/*   Updated: 2024/05/07 14:52:42 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int rev_color(int trgb)
{
	int t;
	int r;
	int g;
	int b;

	t = 0;
	r = 0;
	g = 0;
	b = 0;
	t = 255 - get_t(trgb);
	r = 255 - get_r(trgb);
	g = 255 - get_g(trgb);
	b = 255 - get_b(trgb);
	return (t << 24 | r << 16 | g << 8 | b);
}
