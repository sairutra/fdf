/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:42:52 by spenning          #+#    #+#             */
/*   Updated: 2024/05/18 11:48:57 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void	free_all_mlx(t_data *data)
{
	int	index;

	index = 0;
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	while (index < data->rows)
		free(data->map[index++]);
	free(data->map);
	index = 0;
	while (index < data->rows)
		free(data->map_color[index++]);
	free(data->map_color);
	free(data->mlx);
}
