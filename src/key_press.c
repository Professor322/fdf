/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:30:04 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 20:18:57 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_fill_var(int keycode, void *param)
{
	if (keycode == ISO)
	{
		ANGLE_X = -56.000011;
		ANGLE_Y = 0;
		ANGLE_Z = 46.000011;
	}
	if (keycode == PARALLEL)
	{
		ANGLE_X = 0;
		ANGLE_Y = 0;
		ANGLE_Z = 0;
	}
	X_MOVE = SCREEN_WID / 2;
	Y_MOVE = SCREEN_HEI / 2;
	SCALE = STARTING_SCALE;
	event_manip(0, 0, 0, param);
}

int		key_press(int keycode, void *param)
{
	if (keycode == ESC)
		finish_him((void***)param, CLOSE);
	else if (keycode == ISO || keycode == PARALLEL)
		ft_fill_var(keycode, param);
	else if (keycode == Y_UP)
		event_manip(0, 0, Y_UP, param);
	else if (keycode == Y_DOWN)
		event_manip(0, 0, Y_DOWN, param);
	else if (keycode == X_UP)
		event_manip(0, 0, X_UP, param);
	else if (keycode == X_DOWN)
		event_manip(0, 0, X_DOWN, param);
	else if (keycode == Z_UP)
		event_manip(0, 0, Z_UP, param);
	else if (keycode == Z_DOWN)
		event_manip(0, 0, Z_DOWN, param);
	else if (keycode == HEY)
		event_manip(0, 0, HEY, param);
	return (0);
}
