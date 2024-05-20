/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coordinate_color.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:59:08 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 16:35:35 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int	parse_rows_check_coordinate_color_rgb_hex(char *r, char *g, char *b)
{
	int	hex;

	hex = hstoi(r);
	if (hex < 0 || hex > 255)
		return (EXIT_FAILURE);
	hex = hstoi(g);
	if (hex < 0 || hex > 255)
		return (EXIT_FAILURE);
	hex = hstoi(b);
	if (hex < 0 || hex > 255)
		return (EXIT_FAILURE);
	return (0);
}

// debug
// ft_printf("buf: %s buf[0]: %c buf[1]: %c\n", buf, buf[0], buf[1]);
// ft_printf("hex %d\n", hex);
int	parse_rows_check_coordinate_color_rgb(char *buf)
{
	char	hex_r[3];
	char	hex_g[3];
	char	hex_b[3];

	hex_r[0] = buf[2];
	hex_r[1] = buf[3];
	hex_r[2] = 0;
	hex_g[0] = buf[4];
	hex_g[1] = buf[5];
	hex_g[2] = 0;
	hex_b[0] = buf[6];
	hex_b[1] = buf[7];
	hex_b[2] = 0;
	if (buf[0] != '0' || buf[1] != 'x')
		return (EXIT_FAILURE);
	if (parse_rows_check_coordinate_color_rgb_hex(hex_r, hex_g, hex_b))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_rows_check_coordinate_color_rg(char *buf)
{
	char	hex_r[3];
	char	hex_g[3];
	int		hex;

	hex_r[0] = buf[2];
	hex_r[1] = buf[3];
	hex_r[2] = 0;
	hex_g[0] = buf[4];
	hex_g[1] = buf[5];
	hex_g[2] = 0;
	if (buf[0] != '0' && buf[1] != 'x')
		return (EXIT_FAILURE);
	hex = hstoi(hex_r);
	if (hex < 0 || hex > 255)
		return (EXIT_FAILURE);
	hex = hstoi(hex_g);
	if (hex < 0 || hex > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_rows_check_coordinate_color_r(char *buf)
{
	char	hex_r[3];
	int		hex;

	hex_r[0] = buf[2];
	hex_r[1] = buf[3];
	hex_r[2] = 0;
	if (buf[0] != '0' && buf[1] != 'x')
		return (EXIT_FAILURE);
	hex = hstoi(hex_r);
	if (hex < 0 || hex > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parse_rows_check_coordinate_color(char *buf, char *bv, char *bc)
{
	int	len;
	int	unvalid;

	unvalid = 0;
	len = ft_strlen(bc);
	if (len == 4)
		unvalid = parse_rows_check_coordinate_color_r(bc);
	else if (len == 6)
		unvalid = parse_rows_check_coordinate_color_rg(bc);
	else if (len == 8 || (len == 9 && bc[8] == '\n'))
		unvalid = parse_rows_check_coordinate_color_rgb(bc);
	else
		return (EXIT_FAILURE);
	unvalid = parse_rows_check_coordinate_value(bv);
	if ((ft_strlen(buf) - 1) != ft_strlen(bv) + ft_strlen(bc))
		return (EXIT_FAILURE);
	return (unvalid);
}
