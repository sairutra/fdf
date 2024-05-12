/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:51:29 by spenning          #+#    #+#             */
/*   Updated: 2024/05/12 14:56:25 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"



// void map_init_coordinates(t_data *img)
// {
	
// }

void map_init(t_data *img)
{
	img->map = ft_calloc(1 , sizeof(int[img->rows][img->columns]));
	img->map_color = ft_calloc(1 , sizeof(int[img->rows][img->columns]));
	if (img->map == NULL || img->map_color == NULL)
		return;
	// map_init_coordinates(img);
}


void parse(char **argv, t_data* img)
{
	char	*path;

	path = argv[1];
	img->columns = parse_colom(path);
	img->rows = parse_rows(path, img->columns);
	if (img->columns == -1 || img->rows == -1)
	{
		get_next_line(0, 2);
		ft_printf("columns: %d rows: %d\n", img->columns, img->rows);
		exit(EXIT_FAILURE);
	}
	// map_init(img);
	// if (img->map == NULL || img->map_color == NULL)
	// 	exit(EXIT_FAILURE);
}

