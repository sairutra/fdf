/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spenning <spenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:51:10 by spenning          #+#    #+#             */
/*   Updated: 2024/05/20 18:01:22 by spenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/fdf.h"
#include <stdarg.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>

void	ft_debug(char *format, ...)
{
	va_list	ptr;

	if (DEBUG == 1)
	{
		va_start(ptr, format);
		ft_printf(format, ptr);
		va_end(ptr);
	}
}
