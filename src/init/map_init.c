/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:49:54 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 16:47:23 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int nhti(char *hex, int n)
{
	int index;
	unsigned char byte;
	unsigned int val;

	val = 0;
	index = 0;
	while (index < n)
	{
		byte = hex[index++];
		if (byte >= '0' && byte <= '9') 
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f') 
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F') 
			byte = byte - 'A' + 10;
		else 
			val += 1000;
		val = (val << 4) | (byte & 0xF);
	}
	return(val);
}

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
void map_init_coordinates(t_data *data)
{
	int	fd;
	int index;
	char *buf;
	
	index = 0;
	fd = open(data->map_path, O_RDONLY);
	if (fd == -1)
	{
		free_all_mlx(data);
		exit(EXIT_FAILURE);
	}
	get_next_line(fd, 2);
	while (index < data->rows)
	{
		buf = get_next_line(fd, 0);
		if (buf == NULL && index < data->rows)
		{
			ft_printf("map init buf == NULL && index < data->rows\n");
			free_all_mlx(data);
			exit(EXIT_FAILURE);
		}
		ft_printf("map init buf  %s", buf);
		if (map_init_coordinates_values(data, buf, index))
		{
			ft_printf("map init if(map_init_coordinates_values(data, buf, index)\n");
			free(buf);
			free_all_mlx(data);
			exit(EXIT_FAILURE);
		}
		ft_printf("if(buf)\n");
		if(buf)
			free(buf);
		index++;
	}
}

void map_init(t_data *data)
{
	int index;
	index = 0;

	data->map = (int**)ft_calloc(data->rows, sizeof(int*));
	if (data->map == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	while (index < data->rows)
	{
		data->map[index] = (int*)ft_calloc(data->columns + 1, sizeof(int));
		if (data->map[index] == NULL)
		{
			mlx_destroy_window(data->mlx, data->win);
			mlx_destroy_display(data->mlx);
			free(data->mlx);
			exit(EXIT_FAILURE);
		}
		index++;
	}
	index = 0;
	data->map_color = (int**)ft_calloc(data->rows, sizeof(int*));
	if (data->map_color == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	while (index < data->rows)
	{
		data->map_color[index] = (int*)ft_calloc(data->columns + 1, sizeof(int));
		if (data->map_color[index] == NULL)
		{
			mlx_destroy_window(data->mlx, data->win);
			mlx_destroy_display(data->mlx);
			free(data->mlx);
			exit(EXIT_FAILURE);
		}
		index++;
	}
	ft_printf("hello\n");
	map_init_coordinates(data);
	for (int r = 0; r < data->rows; r++)
	{
		for (int c = 0; c < data->columns; c++)
		{
			ft_printf("x, y, color [%d, %d, %d] %d \n", r, c, data->map_color[r][c], data->map[r][c]);
		}
	}
}

