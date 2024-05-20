/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:49:54 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 17:26:24 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

// debug
// for (int r = 0; r < data->rows; r++)
// {
// 	for (int c = 0; c < data->columns; c++)
// 	{
// 		ft_printf("x, y, color [%d, %d, %d] %d \n", r, c, 
//data->map_color[r][c], data->map[r][c]);
// 	}
// }
void	map_init(t_data *data)
{
	int	i;

	i = 0;
	data->map = (int **)ft_calloc(data->rows, sizeof(int *));
	if (data->map == NULL)
		free_img(data);
	while (i < data->rows)
	{
		data->map[i] = (int *)ft_calloc(data->columns + 1, sizeof(int));
		if (data->map[i] == NULL)
			free_map(data);
		i++;
	}
	i = 0;
	data->map_color = (int **)ft_calloc(data->rows, sizeof(int *));
	if (data->map_color == NULL)
		free_map(data);
	while (i < data->rows)
	{
		data->map_color[i] = (int *)ft_calloc(data->columns + 1, sizeof(int));
		if (data->map_color[i] == NULL)
			free_map(data);
		i++;
	}
	map_init_coordinates(data);
}
