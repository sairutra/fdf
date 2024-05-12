/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:53:56 by spenning          #+#    #+#             */
/*   Updated: 2024/05/12 14:54:10 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

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
	free(buf);
	if (splitbuf == NULL)
		return (-1);
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
