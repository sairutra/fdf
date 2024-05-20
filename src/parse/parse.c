/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:51:29 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 20:41:44 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int	check_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (ft_strncmp(path + (len - 3), "fdf", 3))
		return (1);
	return (0);
}

void	parse(char **argv, t_data *img)
{
	char	*path;

	path = argv[1];
	if (check_path(path))
		exit(EXIT_FAILURE);
	img->map_path = path;
	img->columns = parse_colom(path);
	img->rows = parse_rows(path, img->columns);
	ft_debug("columns: %d rows: %d\n", img->columns, img->rows);
	if (img->columns <= 0 || img->rows <= 0)
	{
		get_next_line(0, 2);
		ft_debug("columns: %d rows: %d\n", img->columns, img->rows);
		exit(EXIT_FAILURE);
	}
}
