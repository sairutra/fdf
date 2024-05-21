/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:09:32 by spenning          #+#    #+#             */
/*   Updated: 2024/05/21 10:37:52 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "../lib/libft/inc/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		rows;
	int		columns;
	int		**map;
	char	*map_path;
	int		**map_color;
	void	*mlx;
	void	*win;
}				t_data;

typedef struct s_point
{
	int	ox;
	int	oy;
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct s_dxy
{
	int	dx;
	int	dy;
}				t_dxy;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

# ifndef WIDTH
#  define WIDTH 1080
# endif

# ifndef HEIGHT
#  define HEIGHT 800
# endif

# ifndef DEBUG
#  define DEBUG 0
# endif

//colors

//[Description]
//This function can programmatically create a tgrb interger
//which can be used for color manipulation. 
//[Parameters]
//int t(ransparency)
//int r(ed)
//int g(reen)
//int b(lue)
//all parameters expect values 0 <= parameter < 256
//[Return]
//Function returns an integer with all the values
// integrated.
//[Error]
//if one of the parameter is not 0 <= parameter < 256
// then function returns -1
int		trgb(int t, int r, int g, int b);
//[Description]
//This function extracts the t(ransparency) value from an trgb
//integer. Make sure to use trgb integer, which can be created with
// the trgb function. 
//[Parameters]
//int trgb
//[Return]
//Function then returns the value as an int.
//[Error]
// No error value
int		get_t(int trgb);
//[Description]
//This function extracts the r(ed) value from an trgb
//integer. Make sure to use trgb integer, which can be created with
// the create_trgb function. 
//[Parameters]
//int trgb
//[Return]
//Function then returns the value as an int.
//[Error]
// No error value
int		get_r(int trgb);
//[Description]
//This function extracts the g(reen) value from an trgb
//integer. Make sure to use trgb integer, which can be created with
// the create_trgb function. 
//[Parameters]
//int trgb
//[Return]
//Function then returns the value as an int.
//[Error]
// No error value
int		get_g(int trgb);
//[Description]
//This function extracts the b(lue) value from an trgb
//integer. Make sure to use trgb integer, which can be created with
// the create_trgb function. 
//[Parameters]
//int trgb
//[Return]
//Function then returns the value as an int.
//[Error]
// No error value
int		get_b(int trgb);
//[Description]
//This function adds shade to a trgb integer 
//[Parameters]
//double distance
//int trgb
//distance expects to be between 0 and 1
//[Return]
//Function returns tgrb integer with modified shade
// values
//[Error]
//if distance is not between 0 and 1
// then function returns -1
int		add_shade(double distance, int color);
//[Description]
//This function take a trgb integer and reverse the color 
//[Parameters]
//int trgb
//[Return]
//Function returns tgrb integer with reverse color
// values
//[Error]
// No error value
int		rev_color(int trgb);

//events

//[Description]
//This function initialize the hooks that will be used
//for the program.
//[Parameters]
//t_vars *vars
//This parameter needs to be initialized with a mlx instance, 
// and a window in order for the hooks to be initiliazed.
//[Return]
//Function returns nothing
// values
//[Error]
// No error value
void	hooks(t_data *data);

//render

//[Description]
//This function put the right values at the memory location of 
// the pixels of a window.
//[Parameters]
//t_data *data
//int x (width)
//int y (height)
//int color (trgb)
//[Return]
//Function returns nothing
// values
//[Error]
// No error value
void	pixel_put(t_data *data, int x, int y, int color);

void	isometric(t_point *a, t_point *b);
void	rotate_x(t_point *a, t_point *b, int alpha);
void	rotate_y(t_point *a, t_point *b, int tetha);
void	rotate_z(t_point *a, t_point *b, int gamma);
void	draw_map(t_data *data);
void	calculate_slope(t_data *data, t_point *a, t_point *b);
int		cal_color(t_point *a, t_point *b);
//init

//[Description]
//This function initializes the data struct, which is used
// to contain data regarding the mlx instance, window, image
// and the map used in the program.
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	data_init(t_data *data);
//[Description]
//This function initializes the map coordinates used in the program.
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	map_init_coords(t_data *data);
//[Description]
//This function initializes the map used in the program.
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	map_init(t_data *data);

//free

//[Description]
//This function frees the display, the mlx instance, and
// exits the program
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	free_dis(t_data *data);
//[Description]
//This function frees the window, display, the mlx instance, and
// exits the program
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	free_win(t_data *data);
//[Description]
//This function frees the image, window, display, the mlx instance, and
// exits the program
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	free_img(t_data *data);
//[Description]
//This function frees the map, image, window, display, 
// the mlx instance, and exits the program
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	free_map(t_data *data);
//[Description]
//This function free's all the data related to mlx and the 
// fdf program
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	free_all_mlx(t_data *data);

//parse

//[Description]
//This function parse the map and checks if the map is valid 
// for the program to run.
//[Parameters]
//char **argv
//t_data *data
//[Return]
//Function returns nothing
// values
//[Error]
// No error value
void	parse(char **argv, t_data *img);
//[Description]
//This function parses the first line of the map, to get
// the count of columns in the map
//[Parameters]
//char *path (to map)
//[Return]
//the count of coloms or an error value
// values
//[Error]
// -1 
int		parse_colom(char *path);
//[Description]
//This function parses all the rows in the map, 
// and checks if the all coordinates are valid
//[Parameters]
//char *path (to map)
//int	colomns (count)
//[Return]
//the number of rows or an error value
//[Error]
// -1 
int		parse_rows(char *path, int columns);
//[Description]
//This function checks a specific coordinate in the form
// of a char *, and returns if it is valid or not. It can accept 
// coordinates with color or without
//[Parameters]
//char *buf
//Function returns 0 if coordinate is valid, otherwise
// it returns the error value
//[Error]
// 1
int		parse_rows_check_coordinate(char *buf);
//[Description]
//This function checks a specific coordinate's value in the form
// of a char *, and returns if it is valid or not.
//[Parameters]
//char *buf
//Function returns 0 if coordinate is valid, otherwise
// it returns the error value
//[Error]
// 1
int		parse_rows_check_coordinate_value(char *buf);
//[Description]
//This function checks a specific coordinate's color, if it is present, 
//in the form of a char *, and returns if it is valid or not.
//[Parameters]
//char *buf
//Function returns 0 if coordinate is valid, otherwise
// it returns the error value
//[Error]
// 1
int		parse_rows_check_coordinate_color(char *buf, char *bv, char *bc);

//utils

//[Description]
//This function takes a string and returns the integer value from based
// based on hexidecimal values. the string should be a represenatiation
// of a hexidecimal value, it for n indices.
//[Parameters]
//char *hex
//int n
//Function returns hexidecimal value in integer represenation, otherwise
// it returns the error value
//[Error]
// the calculated value in the function minus 1000000 to indicate the 
// string based is wrong
int		nhti(char *hex, int n);
//[Description]
//This function takes a string and returns the integer value from based
// based on hexidecimal values. the string should be a represenatiation
// of a hexidecimal value 
//[Parameters]
//char *hex
//Function returns hexidecimal value in integer represenation, otherwise
// it returns the error value
//[Error]
// the calculated value in the function minus 1000000 to indicate the 
// string based is wrong
int		hstoi(char *hex);
//[Description]
//This function used to debug, if during compilation the debug flag is used
// parameters are the same as ft_printf
// with -D DEBUG=1
//[Parameters]
//char *format
//variables
//prints out the paremeters
//[Error]
// No error value
void	ft_debug(char *format, ...);

#endif