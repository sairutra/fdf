/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coordinate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:57:51 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 16:23:42 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

// debug parse_rows_check_coordinate_value 
// ft_printf("index %d len %d\n", index, len);
int	parse_rows_check_coordinate_value(char *buf)
{
	int	len;
	int	index;

	index = 0;
	len = ft_strlen(buf);
	if (buf[len - 1] == '\n')
		len--;
	if (buf[0] == '-')
		index++;
	while (index < len)
	{
		if (!ft_isdigit(buf[index]))
			return (EXIT_FAILURE);
		index++;
	}
	return (EXIT_SUCCESS);
}

int	parse_rows_check_coordinate_atoitoa(char *buf)
{
	int		cmp_int;
	char	*cmp_str;
	int		len;

	len = ft_strlen(buf);
	if (buf[len - 1] == '\n')
		len --;
	cmp_int = ft_atoi(buf);
	cmp_str = ft_itoa(cmp_int);
	if (cmp_str == NULL)
		return (EXIT_FAILURE);
	if (ft_strncmp(buf, cmp_str, len))
	{
		free(cmp_str);
		return (EXIT_FAILURE);
	}
	free(cmp_str);
	return (EXIT_SUCCESS);
}

// debug parse_rows_check_coordinate
// ft_printf("buf %s, atoi %d\n", buf, ft_atoi(sb[0]));
int	parse_rows_check_coordinate_(char **sb, char *buf)
{
	int	unvalid;

	unvalid = 0;
	if (buf[ft_strlen(buf) - 1] == ',')
		unvalid = 1;
	if (sb[1] == NULL)
		unvalid = parse_rows_check_coordinate_value(sb[0]);
	if (sb[1] != NULL)
		unvalid = parse_rows_check_coordinate_color(buf, sb[0], sb[1]);
	return (unvalid);
}

int	parse_rows_check_coordinate(char *buf)
{
	char	**sb;
	int		unvalid;

	unvalid = 0;
	if (!ft_isdigit(buf[0]) && buf[0] != '-')
		return (EXIT_FAILURE);
	sb = ft_split(buf, ',');
	if (sb == NULL)
		return (EXIT_FAILURE);
	if (!parse_rows_check_coordinate_atoitoa(sb[0]))
		unvalid = 0;
	else if (!ft_strncmp(sb[0], "0", 1))
		unvalid = 0;
	else
	{
		free_char_array(sb);
		return (EXIT_FAILURE);
	}
	unvalid = parse_rows_check_coordinate_(sb, buf);
	free_char_array(sb);
	return (unvalid);
}
