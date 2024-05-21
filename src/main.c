/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:43:03 by spenning          #+#    #+#             */
/*   Updated: 2024/05/21 17:42:09 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
		parse(argv, &data);
	else
	{
		perror("Wrong input, provide only with relative path to .fdf file");
		return (EXIT_FAILURE);
	}
	data_init(&data);
	draw_map(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	hooks(&data);
	mlx_loop(data.mlx);
}
