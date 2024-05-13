/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:42:52 by spenning          #+#    #+#             */
/*   Updated: 2024/05/13 22:15:55 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void	free_all_mlx(t_data *data)
{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		for (int i = 0; i < data->rows; i++)
			free(data->map[i]);
		free(data->map);
		for (int i = 0; i < data->rows; i++)
			free(data->map_color[i]);
		free(data->map_color);
		free(data->mlx);
		// get_next_line(0, 2);
}
