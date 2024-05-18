/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:22:50 by spenning          #+#    #+#             */
/*   Updated: 2024/05/18 11:46:56 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int	keypress(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		free_all_mlx(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	destroy(t_data *data)
{
	free_all_mlx(data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	hooks(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, keypress, data);
	mlx_hook(data->win, 17, 0L, destroy, data);
}
