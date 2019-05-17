/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:01:11 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 20:00:59 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_starting_values(void *param, int fd)
{
	MATRIX = get_coords(fd);
	SCREEN_WID = WIDTH;
	SCREEN_HEI = HEIGHT;
	SCALE = STARTING_SCALE;
	GRAB = 0;
	ANGLE_X = 0;
	ANGLE_Y = 0;
	ANGLE_Z = 0;
	X_MOVE = SCREEN_WID / 2;
	Y_MOVE = SCREEN_HEI / 2;
	X_GRAB = 0;
	Y_GRAB = 0;
}

t_fdf		*init(int fd)
{
	t_fdf	*param;

	if (!(param = (t_fdf*)malloc(sizeof(t_fdf))))
		finish_him(NULL, ERR);
	if (!(param->map = (t_mapstate*)malloc(sizeof(t_mapstate))))
		finish_him((void***)param, ERR_AND_DEL_ONE);
	if (!(param->image = (t_image*)malloc(sizeof(t_image))))
	{
		ft_memdel((void**)&(param->map));
		finish_him((void***)param, ERR_AND_DEL_ONE);
	}
	set_starting_values((void*)param, fd);
	MLX_PTR = mlx_init();
	WIN_PTR = mlx_new_window(MLX_PTR, SCREEN_WID, SCREEN_HEI, "FDF");
	IMG_PTR = mlx_new_image(MLX_PTR, SCREEN_WID, SCREEN_HEI);
	_DATA = (int*)mlx_get_data_addr(IMG_PTR,
			&BITS_PER_PIXEL, &SIZE_LINE, &ENDIAN);
	return (param);
}
