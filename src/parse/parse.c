/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:51:29 by spenning          #+#    #+#             */
/*   Updated: 2024/05/12 17:01:46 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

void parse(char **argv, t_data* img)
{
	char	*path;

	path = argv[1];
	img->map_path = path;
	img->columns = parse_colom(path);
	img->rows = parse_rows(path, img->columns);
	if (img->columns == -1 || img->rows == -1)
	{
		get_next_line(0, 2);
		ft_printf("columns: %d rows: %d\n", img->columns, img->rows);
		exit(EXIT_FAILURE);
	}
}

