/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_success.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:42:52 by spenning          #+#    #+#             */
/*   Updated: 2024/05/21 17:51:57 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void	free_all_mlx_success(t_data *data)
{
	int	index;

	index = 0;
	get_next_line(0, 2);
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
	exit(EXIT_SUCCESS);
}
