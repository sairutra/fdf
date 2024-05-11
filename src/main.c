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

int parse_rows_check_coordinate_color(char *buf)
{
	(void)buf;
	// check hexidecimal value
	return(EXIT_SUCCESS);
}

int parse_rows_check_coordinate(char *buf)
{
	char	**splitbuf;
	int		unvalid;

	unvalid = 0;
	splitbuf = ft_split(buf, ',');
	if (splitbuf == NULL)
		return (EXIT_FAILURE);
	if (ft_atoi(splitbuf[0]))
		unvalid = 0;
	else if (!ft_strncmp(splitbuf[0], "0", 1))
		unvalid = 0;
	else
		unvalid = 1;
	if (splitbuf[1] != NULL)
	{	
		if (parse_rows_check_coordinate_color(splitbuf[1]))
			unvalid = 1;
	}
	free_char_array(splitbuf);
	return (unvalid);
}

int parse_rows_check_column(char *buf, int columns)
{
	char	**splitbuf;
	int		count;

	count = 0;
	splitbuf = ft_split(buf, ' ');
	if (splitbuf == NULL)
		return (EXIT_FAILURE);
	while (splitbuf[count] != NULL)
	{
		if(!ft_strncmp(splitbuf[count], "\n", 1))
			break;
		if (parse_rows_check_coordinate(splitbuf[count]))
		{
			free_char_array(splitbuf);
			return(EXIT_FAILURE);
		}
		else
			count++;
	}
	free_char_array(splitbuf);
	if (count != columns)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

int parse_rows_check(char *buf, int columns)
{
	if(parse_rows_check_column(buf, columns))
		return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int parse_rows(char *path, int columns)
{
	int		count;
	int		fd;
	char	*buf;

	count = 1;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	buf = get_next_line(fd, 1);
	if (buf == NULL)
	{
		close(fd);
		return (-1);
	}
	if (parse_rows_check(buf, columns))
	{
		close(fd);
		return (-1);
	}
	while (buf != NULL)
	{
		count++;
		free(buf);
		buf = get_next_line(fd, 0);
		if(buf == NULL)
			break;
		if (parse_rows_check(buf, columns))
		{
			close(fd);
			return (-1);
		}
	}
	close(fd);
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
	buf = get_next_line(fd, 0);
	close(fd);
	if (buf == NULL)
		return (-1);
	splitbuf = ft_split(buf, ' ');
	if (splitbuf == NULL)
		return (-1);
	free(buf);
	while (splitbuf[count] != NULL)
	{
		if (ft_strncmp(splitbuf[count], " ", 1))
			count++;
	}
	if(!ft_strncmp(splitbuf[count - 1], "\n", 1))
		count--;
	free_char_array(splitbuf);
	return (count);
}


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
	// if (img->columns == -1 || img->rows == -1)
	// 	exit(EXIT_FAILURE);
	// map_init(img);
	// if (img->map == NULL || img->map_color == NULL)
	// 	exit(EXIT_FAILURE);
	ft_printf("columns: %d rows: %d", img->columns, img->rows);
}

//look at perror and strerror

void vars_init(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "fdf");
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
	
	color = create_trgb(200, 100, 0, 0);
	vars_init(&vars);
	img_init(&img, &vars);
	draw_squares(&img, img.width, img.height, rev_color(color));
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	hooks(&vars);
	mlx_loop(vars.mlx);
}