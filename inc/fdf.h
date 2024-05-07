/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:09:32 by spenning          #+#    #+#             */
/*   Updated: 2024/05/07 14:56:39 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>

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
#endif
