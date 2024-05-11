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

int parse_rows(char *path)
{
	int		count;
	int		fd;
	char	*buf;

	count = 1;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	buf = get_next_line(fd);
	while (buf != NULL)
	{
		count++;
		free(buf);
		buf = get_next_line(fd);
	}
	close(fd);
	free(buf);
	return (count - 1);
}

int parse_colom(char *path)
{
	int		count;
	int		fd;
	char	*buf;
	char	**splitbuf;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	buf = get_next_line(fd);
	close(fd);
	if (buf == NULL)
		return (-1);
	splitbuf = ft_split(buf, ' ');
	free(buf);
	while (splitbuf[count] != NULL)
	{
		ft_printf("splitbuf[count] %s\n", splitbuf[count]);
		if (ft_strncmp(splitbuf[count], " ", 1))
			count++;
	}
	if(!ft_strncmp(splitbuf[count - 1], "\n", 1))
		count--;
	return (count);
}

void parse(char **argv)
{
	char	*path;
	int		columns;
	int		rows;

	path = argv[1];
	columns = parse_colom(path);
	rows = parse_rows(path);
	ft_printf("columns: %d rows: %d", columns, rows);
}

//look at perror and strerror

int	main(int argc, char **argv)
{	
	int		width;
	int		height;
	int 	color;
	t_data	img;
	t_vars	vars;

	if (argc == 2)
		parse(argv);
	
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