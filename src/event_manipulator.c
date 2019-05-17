/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manipulator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:27:55 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 22:33:35 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	angle_changer(int x, int y, void *param)
{
	if (x - X_GRAB > SENSITIVITY)
		ANGLE_Y += RAT_SPEED;
	else if (x - X_GRAB < -SENSITIVITY)
		ANGLE_Y -= RAT_SPEED;
	if (y - Y_GRAB > SENSITIVITY)
		ANGLE_X += RAT_SPEED;
	else if (y - Y_GRAB < -SENSITIVITY)
		ANGLE_X -= RAT_SPEED;
}

void	grab_and_move(int x, int y, void *param)
{
	if (x != X_GRAB)
	{
		X_MOVE -= X_GRAB - x;
		X_GRAB = x;
	}
	if (y != Y_GRAB)
	{
		Y_MOVE -= Y_GRAB - y;
		Y_GRAB = y;
	}
}

void	map_changer(int x, int y, int flag, void *param)
{
	if (flag == LEFT_MB)
		grab_and_move(x, y, param);
	else if (flag == RIGHT_MB)
		angle_changer(x, y, param);
	else if (flag == MIDDLE_MB)
	{
		X_MOVE = SCREEN_WID / 2;
		Y_MOVE = SCREEN_HEI / 2;
	}
	else if (flag == DOWN_WHEEL || flag == UP_WHEEL)
	{
		SCALE += flag == DOWN_WHEEL ? -SCALE_SPEED : SCALE_SPEED;
		if (SCALE <= 0)
			SCALE = 1;
	}
	else if (flag == X_DOWN || flag == X_UP)
		ANGLE_X += flag == X_DOWN ? -RAT_SPEED : RAT_SPEED;
	else if (flag == Y_DOWN || flag == Y_UP)
		ANGLE_Y += flag == Y_DOWN ? -RAT_SPEED : RAT_SPEED;
	else if (flag == Z_DOWN || flag == Z_UP)
		ANGLE_Z -= flag == Z_DOWN ? -RAT_SPEED : RAT_SPEED;
}

void	event_manip(int x, int y, int flag, void *param)
{
	t_coord		**matrix;
	static int	counter = -1;

	if (!(matrix = strdup_matrix(MATRIX)))
		finish_him(NULL, ERR);
	ft_bzero(_DATA, SCREEN_WID * SCREEN_HEI * sizeof(int));
	map_changer(x, y, flag, param);
	if (flag == HEY)
		counter++;
	counter != 1 ? counter = 0 : gradient_color(matrix);
	scale_map(matrix, param);
	z_rotation(matrix, ANGLE_Z);
	x_rotation(matrix, ANGLE_X);
	y_rotation(matrix, ANGLE_Y);
	move_map(matrix, X_MOVE, Y_MOVE);
	ft_paint_matrix(matrix, (t_fdf*)param);
	mlx_put_image_to_window(MLX_PTR, WIN_PTR, IMG_PTR, 0, 0);
	ft_del_twodem_arr((void***)&matrix);
}
