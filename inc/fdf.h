/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:09:32 by spenning          #+#    #+#             */
/*   Updated: 2024/05/21 17:53:20 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "../lib/libft/inc/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

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

# ifndef WIDTH
#  define WIDTH 1080
# endif

# ifndef HEIGHT
#  define HEIGHT 800
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
//[Error]
// No error value
void	pixel_put(t_data *data, int x, int y, int color);
//[Description]
//This function is used to turn point a and b coordinates
// into isometric view 
//[Parameters]
//t_point *a
//t_point *b
//[Return]
//Function returns nothing
//[Error]
// No error value
void	isometric(t_point *a, t_point *b);
//[Description]
//This function is used to turn point a and b y, z coordinates
// based on alpha value 
//[Parameters]
//t_point *a
//t_point *b
//int alpha
//[Return]
//Function returns nothing
//[Error]
// No error value
void	rotate_x(t_point *a, t_point *b, int alpha);
//[Description]
//This function is used to turn point a and b x, z coordinates
// based on tetha value 
//[Parameters]
//t_point *a
//t_point *b
//int tetha
//[Return]
//Function returns nothing
//[Error]
// No error value
void	rotate_y(t_point *a, t_point *b, int tetha);
//[Description]
//This function is used to turn point a and b x, y coordinates
// based on gamma value 
//[Parameters]
//t_point *a
//t_point *b
//int gamma
//[Return]
//Function returns nothing
//[Error]
// No error value
void	rotate_z(t_point *a, t_point *b, int gamma);
//[Description]
//This function is used to draw the map 
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	draw_map(t_data *data);
//[Description]
//This function is used to calculate the slope between
// point a and b, and then draws the line in between 
//[Parameters]
//t_point *a
//t_point *b
//[Return]
//Function returns nothing
//[Error]
// No error value
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
//[Description]
//This function free's all the data related to mlx and the 
// fdf program and exits with success code
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	free_all_mlx_success(t_data *data);

//parse

//[Description]
//This function parse the map and checks if the map is valid 
// for the program to run.
//[Parameters]
//char **argv
//t_data *data
//[Return]
//Function returns nothing
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
int		parse_rows(int columns, int fd);
//[Description]
//This function checks a specific coordinate in the form
// of a char *, and returns if it is valid or not. It can accept 
// coordinates with color or without
//[Parameters]
//char *buf
//[Return]
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
//[Return]
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
//[Return]
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
//[Return]
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
//[Return]
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
//[Return]
//function returns nothing
//[Error]
// No error value
void	ft_debug(char *format, ...);
//[Description]
//This function gives back the absolute value of the parameter.
// This means the distance between the value and 0
//[Parameters]
//int val
//[Return]
// returns absolute value
//[Error]
// No error value
int		fdf_abs(int val);

#endif