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

void vars_init(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		exit(EXIT_FAILURE);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "fdf");
	if (vars->win == NULL)
	{
		free(vars->mlx);
		exit(EXIT_FAILURE);
	}
}

void img_init(t_data *img, t_vars *vars)
{
	img->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	img->width = WIDTH;
	img->height = HEIGHT;
}

int	main(int argc, char **argv)
{	
	int 	color;
	t_data	img;
	t_vars	vars;

	if (argc == 2)
		parse(argv, &img);
	else
		return(EXIT_FAILURE);
	color = create_trgb(200, 100, 0, 0);
	vars_init(&vars);
	img_init(&img, &vars);
	draw_squares(&img, img.width, img.height, rev_color(color));
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	hooks(&vars);
	mlx_loop(vars.mlx);
}