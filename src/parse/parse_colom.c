/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:53:56 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 16:42:52 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

char	**parse_colom_split(int fd)
{
	char	*buf;
	char	**splitbuf;

	if (fd == -1)
		return (NULL);
	buf = get_next_line(fd, 0);
	close(fd);
	if (buf == NULL)
		return (NULL);
	splitbuf = ft_split(buf, ' ');
	free(buf);
	if (splitbuf == NULL)
		return (NULL);
	return (splitbuf);
}

int	parse_colom(char *path)
{
	int		count;
	int		fd;
	char	**splitbuf;

	count = 0;
	fd = open(path, O_RDONLY);
	splitbuf = parse_colom_split(fd);
	if (splitbuf == NULL)
		return (-1);
	while (splitbuf[count] != NULL)
	{
		if (ft_strncmp(splitbuf[count], " ", 1))
			count++;
	}
	if (!ft_strncmp(splitbuf[count - 1], "\n", 1))
		count--;
	free_char_array(splitbuf);
	return (count);
}
