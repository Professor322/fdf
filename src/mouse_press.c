/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:54:33 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 22:38:33 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_press(int button, int x, int y, void *param)
{
	if (button == UP_WHEEL)
		event_manip(x, y, UP_WHEEL, param);
	else if (button == DOWN_WHEEL)
		event_manip(x, y, DOWN_WHEEL, param);
	else if (button == LEFT_MB)
	{
		if (x >= 0 && y >= 0 && y <= SCREEN_WID - 1 && x <= SCREEN_HEI - 1)
			GRAB = LEFT_MB;
		X_GRAB = x;
		Y_GRAB = y;
	}
	else if (button == RIGHT_MB)
	{
		if (x >= 0 && y >= 0 && y <= SCREEN_WID - 1 && x <= SCREEN_HEI - 1)
			GRAB = RIGHT_MB;
		X_GRAB = x;
		Y_GRAB = y;
	}
	else if (button == MIDDLE_MB)
		event_manip(0, 0, MIDDLE_MB, param);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	if (x >= 0 && y >= 0 && y <= SCREEN_WID - 1 && x <= SCREEN_HEI - 1)
	{
		if (GRAB == LEFT_MB)
			event_manip(x, y, LEFT_MB, param);
		else	if (GRAB == RIGHT_MB)
			event_manip(x, y, RIGHT_MB, param);
	}
	return (0);
}

int		mouse_release(int button, int x, int y, void *param)
{
	x = 0;
	y = 0;
	if (button == LEFT_MB)
		GRAB = 0;
	else if (button == RIGHT_MB)
		GRAB = 0;
	return (0);
}

int		ft_close(void *param)
{
	finish_him((void***)param, CLOSE);
	return (0);
}
