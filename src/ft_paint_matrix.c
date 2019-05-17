/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:12:14 by jziemann          #+#    #+#             */
/*   Updated: 2019/03/20 19:42:34 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_matrix(t_coord **matrix, void *param)
{
	register int i;
	register int j;

	i = 0;
	while (i < g_height - 1)
	{
		j = 0;
		while (j < g_length - 1)
		{
			draw_line(matrix[i][j], matrix[i + 1][j], param);
			draw_line(matrix[i][j], matrix[i][j + 1], param);
			draw_line(matrix[g_height - 1][j],
					matrix[g_height - 1][j + 1], param);
			j++;
		}
		draw_line(matrix[i][g_length - 1], matrix[i + 1][g_length - 1], param);
		i++;
	}
}

static void	draw_dot_and_line(t_coord **matrix, void *param)
{
	register int i;
	register int j;

	i = 0;
	j = 0;
	if (g_height == 1 && g_length != 1)
	{
		while (j < g_length - 1)
		{
			draw_line(matrix[i][j], matrix[i][j + 1], param);
			j++;
		}
	}
	else if (g_height != 1 && g_length == 1)
	{
		while (i < g_height - 1)
		{
			draw_line(matrix[i][j], matrix[i + 1][j], param);
			i++;
		}
	}
	else
		draw_line(matrix[i][j], matrix[i][j], param);
}

void		ft_paint_matrix(t_coord **matrix, void *param)
{
	if (g_height != 1 && g_length != 1)
		draw_matrix(matrix, param);
	else
		draw_dot_and_line(matrix, param);
}
