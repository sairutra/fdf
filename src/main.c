#include "../inc/fdf.h"
#include <stdio.h>

void draw_rows(t_data *img, int width, int height, int trgb)
{
	int windex;
	int hindex;

	windex = 0;
	hindex = 0;
	while (height >= 0)
	{
		while (hindex <= 100)
		{
			while (windex <= width)
			{
				if ((height - hindex) >= 0)
					pixel_put(img, windex, height - hindex, trgb);
				windex++;
			}
			windex = 0;
			hindex++;
		}
		hindex = 0;
		height -= 200;
	}
}

void draw_columns(t_data *img, int width, int height, int trgb)
{
	int windex;
	int hindex;

	windex = 0;
	hindex = 0;
	while (width >= 0)
	{
		while (windex <= 100)
		{
			while (hindex <= height)
			{
				if ((width - windex) >= 0)
					pixel_put(img, width - windex, hindex, trgb);
				hindex++;
			}
			hindex = 0;
			windex++;
		}
		windex = 0;
		width -= 200;
	}
}

void draw_squares(t_data *img, int width, int height, int trgb)
{
	draw_rows(img, width, height, trgb);
	draw_columns(img, width, height, trgb);
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
		free_all(data);
	data->width = WIDTH;
	data->height = HEIGHT;
}

int	main(int argc, char **argv)
{	
	int 	color;
	t_data	data;

	if (argc == 2)
		parse(argv, &data);
	else
		return(EXIT_FAILURE);
	color = create_trgb(200, 100, 0, 0);
	data_init(&data);
	draw_squares(&data, data.width, data.height, rev_color(color));
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	hooks(&data);
	mlx_loop(data.mlx);
}