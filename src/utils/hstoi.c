/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hstoi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 14:59:08 by spenning          #+#    #+#             */
/*   Updated: 2024/05/21 09:11:12 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"

int	nhti(char *hex, int n)
{
	int				index;
	unsigned char	byte;
	unsigned int	val;

	val = 0;
	index = 0;
	while (index < n)
	{
		byte = hex[index++];
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		else
			val -= 1000000;
		val = (val << 4) | (byte & 0xF);
	}
	ft_debug("hex %s value %d\n", hex, val);
	return (val);
}

int	hstoi(char *hex)
{
	int				index;
	unsigned char	byte;
	unsigned int	val;

	val = 0;
	index = 0;
	while (hex[index] != 0)
	{
		byte = hex[index++];
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		else
			val -= 1000000;
		val = (val << 4) | (byte & 0xF);
	}
	return (val);
}
