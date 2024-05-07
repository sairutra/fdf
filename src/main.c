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

int	main(void)
{	
	int		width;
	int		height;
	int 	color;
	t_data	img;
	t_vars	vars;

	color = create_trgb(200, 100, 0, 0);
	width = 1920;
	height = 1080;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	draw_squares(&img, width, height, rev_color(color));
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	hooks(&vars);
	mlx_loop(vars.mlx);
}