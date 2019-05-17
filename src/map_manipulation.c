/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:47:35 by jziemann          #+#    #+#             */
/*   Updated: 2019/03/20 20:03:42 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_map(t_coord **matrix, void *param)
{
	register int i;
	register int j;

	i = 0;
	while (i < g_height)
	{
		j = 0;
		while (j < g_length)
		{
			(*(matrix + i) + j)->x *= SCALE;
			(*(matrix + i) + j)->y *= SCALE;
			(*(matrix + i) + j)->z *= SCALE;
			j++;
		}
		i++;
	}
}

void	x_rotation(t_coord **m, float angle)
{
	register int	i;
	register int	j;
	float			alpha;
	int				prev_y;
	int				prev_z;

	alpha = angle * (PI / 180);
	i = 0;
	while (i < g_height)
	{
		j = 0;
		while (j < g_length)
		{
			prev_y = (*(m + i) + j)->y;
			prev_z = (*(m + i) + j)->z;
			(*(m + i) + j)->y = prev_y * cos(alpha) + prev_z * sin(alpha);
			(*(m + i) + j)->z = -prev_y * sin(alpha) + prev_z * cos(alpha);
			j++;
		}
		i++;
	}
}

void	y_rotation(t_coord **m, float angle)
{
	register int	i;
	register int	j;
	int				prev_x;
	int				prev_z;
	float			alpha;

	alpha = angle * (PI / 180);
	i = 0;
	while (i < g_height)
	{
		j = 0;
		while (j < g_length)
		{
			prev_x = (*(m + i) + j)->x;
			prev_z = (*(m + i) + j)->z;
			(*(m + i) + j)->x = prev_x * cos(alpha) + prev_z * sin(alpha);
			(*(m + i) + j)->z = -prev_x * sin(alpha) + prev_z * cos(alpha);
			j++;
		}
		i++;
	}
}

void	z_rotation(t_coord **m, float angle)
{
	register int	i;
	register int	j;
	int				prev_x;
	int				prev_y;
	float			alpha;

	alpha = angle * (PI / 180);
	i = 0;
	while (i < g_height)
	{
		j = 0;
		while (j < g_length)
		{
			prev_x = (*(m + i) + j)->x;
			prev_y = (*(m + i) + j)->y;
			(*(m + i) + j)->x = prev_x * cos(alpha) - prev_y * sin(alpha);
			(*(m + i) + j)->y = prev_x * sin(alpha) + prev_y * cos(alpha);
			j++;
		}
		i++;
	}
}

void	move_map(t_coord **m, int x_move, int y_move)
{
	register int i;
	register int j;

	i = 0;
	while (i < g_height)
	{
		j = 0;
		while (j < g_length)
		{
			(*(m + i) + j)->x += x_move;
			(*(m + i) + j)->y += y_move;
			j++;
		}
		i++;
	}
}
