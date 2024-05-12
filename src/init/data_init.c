/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:49:54 by spenning          #+#    #+#             */
/*   Updated: 2024/05/12 18:08:22 by spenning         ###   ########.fr       */
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
	data->map[r][c] = ft_atoi(buf);
	data->map_color[r][c] = trgb(0, 255, 255, 255);
}

int map_init_coordinates_values_vc(t_data *data, char *buf, int r, int c)
{
	char **splitbuf;

	splitbuf = ft_split(buf, ',');
	if (splitbuf == NULL)
		return (EXIT_FAILURE);
	if (splitbuf[1] == NULL)
		map_init_coordinates_values_vc_dft(data, splitbuf[0], r, c);
	else if (splitbuf[1] != NULL)
		map_init_coordinates_values_vc_clr(data, splitbuf, r, c);
	free_char_array(splitbuf);
	return (EXIT_SUCCESS);
}	

int map_init_coordinates_values(t_data *data, char *buf, int row)
{
	int		col;
	char **splitbuf;

	col = 0;
	splitbuf = ft_split(buf, ' ');
	if (splitbuf == NULL)
		return (EXIT_FAILURE);
	while (splitbuf[col] != NULL)
	{
		if (map_init_coordinates_values_vc(data, splitbuf[col], row, col))
		{
			free_char_array(splitbuf);
			return(EXIT_FAILURE);
		}
	}
	free_char_array(splitbuf);
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
	while (index < data->rows)
	{
		buf = get_next_line(fd, 1);
		if (buf == NULL)
		{
			free_all_mlx(data);
			exit(EXIT_FAILURE);
		}
		if (map_init_coordinates_values(data, buf, index))
		{
			free(buf);
			free_all_mlx(data);
			exit(EXIT_FAILURE);
		}
		free(buf);
	}
}

void map_init(t_data *data)
{
	data->map = ft_calloc(1 , sizeof(int[data->rows][data->columns]));
	if (data->map == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->map_color = ft_calloc(1 , sizeof(int[data->rows][data->columns]));
	if(data->map_color == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free(data->map);
		exit(EXIT_FAILURE);
	}
	map_init_coordinates(data);
}

void data_init(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fdf");
	if (data->win == NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);
	if(data->addr == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	map_init(data);
	data->width = WIDTH;
	data->height = HEIGHT;
}