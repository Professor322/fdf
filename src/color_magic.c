/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_magic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jziemann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:08:44 by jziemann          #+#    #+#             */
/*   Updated: 2019/03/20 19:05:46 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		color_intens(int color, float k)
{
	int red;
	int green;
	int blue;
	int coef;

	coef = k * 1000;
	coef = coef / 10 + ((coef % 10 >= 5) ? 1 : 0);
	coef += (coef <= 50 ? 10 : 0);
	blue = (color & 0xff) * k > 0xff ? 0xff :
		((color & 0xff) * coef) / 100 & 0xff;
	green = (color & 0xff00) * k > 0xff00 ? 0xff00 :
		((color & 0xff00) * coef) / 100 & 0xff00;
	red = (color & 0xff0000) * k > 0xff0000 ? 0xff0000 :
		((color & 0xff0000) * coef / 100) & 0xff0000;
	return (red | green | blue);
}

double	percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int		get_color(t_coord current, t_coord start, t_coord end, int flag)
{
	int			red;
	int			green;
	int			blue;
	double		percentage;

	if (current.color == end.color)
		return (current.color);
	if (flag)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xff,
			(end.color >> 16) & 0xff, percentage);
	green = get_light((start.color >> 8) & 0xff,
			(end.color >> 8) & 0xff, percentage);
	blue = get_light((start.color) & 0xff, (end.color) & 0xff, percentage);
	return ((red << 16) | (green << 8) | blue);
}
