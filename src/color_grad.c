/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_grad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 21:41:12 by jziemann          #+#    #+#             */
/*   Updated: 2019/03/20 19:05:15 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		color_step(int start, int end, double percentage)
{
	int red;
	int green;
	int blue;

	red = get_light((start >> 16) & 0xff,
			(end >> 16) & 0xff, percentage);
	green = get_light((start >> 8) & 0xff,
			(end >> 8) & 0xff, percentage);
	blue = get_light((start) & 0xff, (end) & 0xff, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void	find_and_color(t_coord **matrix, int z, int color)
{
	int i;
	int j;

	i = 0;
	while (i < g_height)
	{
		j = 0;
		while (j < g_length)
		{
			if ((*(matrix + i) + j)->z == z)
				(*(matrix + i) + j)->color = color;
			j++;
		}
		i++;
	}
}

void	gradient_coord(t_coord **matrix, int start_color, int end_color)
{
	int		i;
	int		j;
	int		current_color;
	double	percentage;

	i = 0;
	while (i < g_height)
	{
		j = 0;
		while (j < g_length)
		{
			if (!(*(matrix + i) + j)->color || (*(matrix + i) + j)->color == 0)
			{
				percentage = percent(g_min, g_max, (*(matrix + i) + j)->z);
				current_color = color_step(start_color, end_color, percentage);
				(*(matrix + i) + j)->color = current_color;
				find_and_color(matrix, (*(matrix + i) + j)->z, current_color);
			}
			j++;
		}
		i++;
	}
}

int		count_step(t_coord **matrix)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 1;
	while (i < g_height)
	{
		j = 0;
		while (j < g_length)
		{
			if ((*(matrix + i) + j)->z < g_max
					&& (*(matrix + i) + j)->z > g_min)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int		gradient_color(t_coord **matrix)
{
	int i;
	int j;
	int count;
	int current_color;
	int step;

	current_color = COLOR_HOLLOW;
	count = count_step(matrix);
	step = 1 - (-COLOR_HOLLOW + COLOR_TOP) / count;
	i = 0;
	while (i < g_height)
	{
		j = 0;
		while (j < g_length)
		{
			(*(matrix + i) + j)->color = current_color;
			current_color += step;
			j++;
		}
		i++;
	}
	return (1);
}
