/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:42:52 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 17:28:16 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"


void	free_map(t_data *data)
{
	int	index;

	index = 0;
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	while (index < data->rows && data->map[index] != NULL)
		free(data->map[index++]);
	free(data->map);
	if (data->map_color)
	{
		index = 0;
		while (index < data->rows && data->map_color[index] != NULL)
			free(data->map_color[index++]);
		free(data->map_color);
	}
	free(data->mlx);
	exit(EXIT_FAILURE);
}

void	free_img(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_FAILURE);
}

void	free_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_FAILURE);
}

void	free_dis(t_data *data)
{
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_FAILURE);
}

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
	exit(EXIT_FAILURE);
}
