/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_coordinates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:49:54 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 17:32:05 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void map_init_coordinates_values_vc_clr(t_data *data, char **b, int r, int c)
{
	int clr;
	int len;

	clr = trgb(255, 255, 255, 255);
	len = ft_strlen(b[1]);
	if(len == 4)
		clr = trgb(0, nhti(&b[1][2], 1), 0, 0);
	if(len == 6)
		clr = trgb(0, nhti(&b[1][2], 1), nhti(&b[1][4], 1), 0);
	if(len == 8)
		clr = trgb(0, nhti(&b[1][2], 1), nhti(&b[1][4], 1), nhti(&b[1][6], 1));
	data->map[r][c] = ft_atoi(b[0]);
	data->map_color[r][c] = clr;
}

void map_init_coordinates_values_vc_dft(t_data *data, char *buf, int r, int c)
{
	ft_printf("r %d c %d\n", r, c);
	ft_printf("map_init_coordinates_values_vc_dft buf %s\n", buf);
	data->map[r][c] = ft_atoi(buf);
	ft_printf("map_init_coordinates_values_vc_dft tgrb %d\n", trgb(0, 255, 255, 255));
	data->map_color[r][c] = trgb(0, 255, 255, 255);
}

int map_init_coordinates_values_vc(t_data *data, char *buf, int r, int c)
{
	char	**splitbuf;
	int		index;
	index = 0;
	splitbuf = ft_split(buf, ',');
	ft_printf("map init coordinates_values_vc buf %s\n", buf);
	if (splitbuf == NULL)
		return (EXIT_FAILURE);
	while(splitbuf[index] != NULL)
	{
		ft_printf("map init coordinates_values_vc splitbug[index] %s\n", splitbuf[index]);
		index++;
	}
	ft_printf("index: %d\n", index);
	if (index == 1)
		map_init_coordinates_values_vc_dft(data, splitbuf[0], r, c);
	else if (index == 2)
		map_init_coordinates_values_vc_clr(data, splitbuf, r, c);
	ft_printf("map init coordinates_values_vc pre free_char_array\n");
	free_char_array(splitbuf);
	ft_printf("map init coordinates_values_vc after free_char_array\n");
	return (EXIT_SUCCESS);
}	

int map_init_coordinates_values(t_data *data, char *buf, int row)
{
	int		col;
	char **splitbuf;

	col = 0;
	splitbuf = ft_split(buf, ' ');
	ft_printf("map init coordinates_values buf %s\n", buf);
	if (splitbuf == NULL)
		return (EXIT_FAILURE);
	while (splitbuf[col] != NULL)
	{
		ft_printf("map init coordinates_values splitbuf[col] %s\n", splitbuf[col]);
		if (map_init_coordinates_values_vc(data, splitbuf[col], row, col))
		{
			free_char_array(splitbuf);
			return(EXIT_FAILURE);
		}
		col++;
	}
	ft_printf("map init coordinates_values before free char array\n");
	free_char_array(splitbuf);
	ft_printf("map init coordinates_values after free char array\n");
	return (EXIT_SUCCESS);
}

// ft_printf("map init buf == NULL && index < data->rows\n");
// ft_printf("map init buf  %s", buf);
// ft_printf("map init if(map_init_coordinates_values(data, buf, index)\n");
// ft_printf("if(buf)\n");
void	map_init_coordinates(t_data *data)
{
	int		fd;
	int		index;
	char	*buf;

	index = 0;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
		free_all_mlx(data);
	get_next_line(fd, 2);
	while (index < data->rows)
	{
		buf = get_next_line(fd, 0);
		if (buf == NULL && index < data->rows)
			free_all_mlx(data);
		if (map_init_coordinates_values(data, buf, index))
		{
			free(buf);
			free_all_mlx(data);
			exit(EXIT_FAILURE);
		}
		if (buf)
			free(buf);
		index++;
	}
}
