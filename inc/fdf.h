/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:09:32 by spenning          #+#    #+#             */
/*   Updated: 2024/05/12 15:45:09 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include "../lib/libft/inc/libft.h"
#include <unistd.h>
#include <fcntl.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		rows;
	int		columns;
	int		*map;
	int		*map_color;
	void	*mlx;
	void	*win;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

#ifndef WIDTH
# define WIDTH 1920
#endif

#ifndef HEIGHT
# define HEIGHT 1080
#endif

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
int	create_trgb(int t, int r, int g, int b);
//[Description]
//This function extracts the t(ransparency) value from an trgb
//integer. Make sure to use trgb integer, which can be created with
// the create_trgb function. 
//[Parameters]
//int trgb
//[Return]
//Function then returns the value as an int.
//[Error]
// No error value
int	get_t(int trgb);
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
int	get_r(int trgb);
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
int	get_g(int trgb);
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
int	get_b(int trgb);
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
int add_shade(double distance, int color);
//[Description]
//This function take a trgb integer and reverse the color 
//[Parameters]
//int trgb
//[Return]
//Function returns tgrb integer with reverse color
// values
//[Error]
// No error value
int rev_color(int trgb);

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
void hooks(t_data *data);

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

//free_all
//[Description]
//This function free's all the data related to mlx and the 
// fdf program
//[Parameters]
//t_data *data
//[Return]
//Function returns nothing
//[Error]
// No error value
void	free_all(t_data *data);

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
void parse(char **argv, t_data* img);
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
int parse_colom(char *path);
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
int parse_rows(char *path, int columns);
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
int parse_rows_check_coordinate(char *buf);
//[Description]
//This function checks a specific coordinate's value in the form
// of a char *, and returns if it is valid or not.
//[Parameters]
//char *buf
//Function returns 0 if coordinate is valid, otherwise
// it returns the error value
//[Error]
// 1
int parse_rows_check_coordinate_value(char *buf);
//[Description]
//This function checks a specific coordinate's color, if it is present, 
//in the form of a char *, and returns if it is valid or not.
//[Parameters]
//char *buf
//Function returns 0 if coordinate is valid, otherwise
// it returns the error value
//[Error]
// 1
int parse_rows_check_coordinate_color(char *buf, char *bv, char *bc);
#endif
