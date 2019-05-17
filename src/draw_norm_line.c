/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_norm_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:47:15 by jziemann          #+#    #+#             */
/*   Updated: 2019/03/20 19:19:51 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap_coordinate(t_coord *coord1, t_coord *coord2)
{
	ft_swap(&(coord1->x), &(coord2->x));
	ft_swap(&(coord1->y), &(coord2->y));
	ft_swap(&(coord1->z), &(coord2->z));
	ft_swap(&(coord1->color), &(coord2->color));
}

void	check_margins(void *param, int x, int y, int color)
{
	if (x < 0 || y < 0 || y > SCREEN_WID - 1 || x > SCREEN_HEI - 1)
		return ;
	_DATA[y * SCREEN_WID + x] = color;
}

void	draw_dy_line(t_coord coord1, t_coord coord2, void *param, float tan)
{
	float		intery;
	t_coord		current;

	if (coord2.y < coord1.y)
		swap_coordinate(&coord1, &coord2);
	tan = (coord2.x < coord1.x) ? -tan : tan;
	intery = coord1.x + tan;
	current = coord1;
	check_margins(param, coord1.x, current.y++, coord1.color);
	while (current.y < coord2.y)
	{
		current.color = get_color(current, coord1, coord2, 0);
		check_margins(param, (int)intery, current.y,
				color_intens(current.color, 1.0 - (intery - (int)intery)));
		check_margins(param, (int)intery + 1, current.y,
				color_intens(current.color, intery - (int)intery));
		intery += tan;
		current.y++;
	}
	check_margins(param, coord2.x, coord2.y, coord2.color);
}

void	draw_dx_line(t_coord coord1, t_coord coord2, void *param, float tan)
{
	float		intery;
	t_coord		current;

	if (coord2.x < coord1.x)
		swap_coordinate(&coord1, &coord2);
	tan = (coord2.y < coord1.y) ? -tan : tan;
	intery = coord1.y + tan;
	current = coord1;
	check_margins(param, current.x++, coord1.y, coord1.color);
	while (current.x < coord2.x)
	{
		current.color = get_color(current, coord1, coord2, 1);
		check_margins(param, current.x, (int)intery,
				color_intens(current.color, 1.0 - (intery - (int)intery)));
		check_margins(param, current.x, (int)intery + 1,
				color_intens(current.color, intery - (int)intery));
		intery += tan;
		current.x++;
	}
	check_margins(param, coord2.x, coord2.y, coord2.color);
}

void	draw_line(t_coord crd1, t_coord crd2, void *param)
{
	const int	dx = (crd2.x >= crd1.x) ? (crd2.x - crd1.x) : (crd1.x - crd2.x);
	const int	dy = (crd2.y >= crd1.y) ? (crd2.y - crd1.y) : (crd1.y - crd2.y);
	float		tan;

	if (dy < dx)
	{
		tan = (float)dy / dx;
		draw_dx_line(crd1, crd2, param, tan);
	}
	else
	{
		tan = (float)dx / dy;
		draw_dy_line(crd1, crd2, param, tan);
	}
}
