/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_row.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:56:15 by spenning          #+#    #+#             */
/*   Updated: 2024/05/12 14:56:53 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

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
		free(buf);
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
			free(buf);
			close(fd);
			return (-1);
		}
	}
	close(fd);
	return (count - 1);
}
