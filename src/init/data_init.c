/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:49:54 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 16:57:59 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void	data_init_free_addr(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_FAILURE);
}

void	data_init_free_img(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_FAILURE);
}

void	data_init_free_win(t_data *data)
{
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_FAILURE);
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fdf");
	if (data->win == NULL)
		data_init_free_win(data);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img == NULL)
		data_init_free_img(data);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	if (data->addr == NULL)
		data_init_free_addr(data);
	map_init(data);
	data->width = WIDTH;
	data->height = HEIGHT;
}
