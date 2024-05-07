/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:22:50 by spenning          #+#    #+#             */
/*   Updated: 2024/05/07 18:32:29 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int	keypress(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	destroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

void hooks(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L<<0, keypress, vars);
	mlx_hook(vars->win, 17, 0L, destroy, vars);
}
