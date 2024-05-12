/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coordinate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:57:51 by spenning          #+#    #+#             */
/*   Updated: 2024/05/12 15:07:53 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int parse_rows_check_coordinate_value(char *buf)
{
	int	len;
	int index;

	index = 0;
	len = ft_strlen(buf);
	if (buf[len - 1] == '\n')
		len--;
	if(buf[0] == '-')
			index++;
	// ft_printf("index %d len %d\n", index, len);
	while (index < len)
	{
		if (!ft_isdigit(buf[index]))
			return (EXIT_FAILURE); 
		index++;
	}
	return (EXIT_SUCCESS);
}

int parse_rows_check_coordinate_atoitoa(char *buf)
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
		return(EXIT_FAILURE);
	if (ft_strncmp(buf, cmp_str, len))
	{
		free(cmp_str);
		return(EXIT_FAILURE);
	}
	free(cmp_str);
	return(EXIT_SUCCESS);
}

int parse_rows_check_coordinate(char *buf)
{
	char	**splitbuf;
	int		unvalid;

	unvalid = 0;
	if(!ft_isdigit(buf[0]) && buf[0] != '-')
		return (EXIT_FAILURE);
	splitbuf = ft_split(buf, ',');
	// ft_printf("buf %s, atoi %d\n", buf, ft_atoi(splitbuf[0]));
	if (splitbuf == NULL)
		return (EXIT_FAILURE);
	if (!parse_rows_check_coordinate_atoitoa(splitbuf[0]))
		unvalid = 0;
	else if (!ft_strncmp(splitbuf[0], "0", 1))
		unvalid = 0;
	else
	{
		free_char_array(splitbuf);
		return(EXIT_FAILURE);
	}
	if (buf[ft_strlen(buf) - 1] == ',')
		unvalid = 1;
	if (splitbuf[1] == NULL)
		unvalid = parse_rows_check_coordinate_value(splitbuf[0]);
	if (splitbuf[1] != NULL)
			unvalid = parse_rows_check_coordinate_color(buf, splitbuf[0], splitbuf[1]);
	free_char_array(splitbuf);
	return (unvalid);
}

