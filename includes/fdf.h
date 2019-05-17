/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:42:42 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 22:33:33 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FDF_H
# define _FDF_H

# include <mlx.h>
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define WIDTH			1000
# define HEIGHT			1000
# define STARTING_SCALE 25
# define SCALE_SPEED	1
# define RAT_SPEED      2.0
# define SENSITIVITY	1
# define PI				3.14159265359

# define IMG			((t_fdf*)param)->image
# define IMG_PTR		((t_fdf*)param)->image->img_ptr
# define BITS_PER_PIXEL ((t_fdf*)param)->image->bits_per_pixel
# define SIZE_LINE      ((t_fdf*)param)->image->size_line
# define ENDIAN         ((t_fdf*)param)->image->endian
# define _DATA          ((t_fdf*)param)->image->data

# define MAP			((t_fdf*)param)->map
# define X_MOVE			((t_fdf*)param)->map->x_move
# define Y_MOVE			((t_fdf*)param)->map->y_move
# define X_GRAB         ((t_fdf*)param)->map->x_grab
# define Y_GRAB         ((t_fdf*)param)->map->y_grab
# define SCALE	 		((t_fdf*)param)->map->scale
# define ANGLE_X        ((t_fdf*)param)->map->x_angle
# define ANGLE_Y        ((t_fdf*)param)->map->y_angle
# define ANGLE_Z        ((t_fdf*)param)->map->z_angle

# define SCREEN_WID 	((t_fdf*)param)->screen_width
# define SCREEN_HEI 	((t_fdf*)param)->screen_height
# define MATRIX 		((t_fdf*)param)->matrix
# define _MATRIX(i, j) 	((t_fdf*)param)->matrix[i][j]
# define GRAB			((t_fdf*)param)->grab
# define MLX_PTR        ((t_fdf*)param)->mlx_ptr
# define WIN_PTR        ((t_fdf*)param)->win_ptr

# define COLOR_LOWLAND	0X00FA9A
# define COLOR_HILL		0Xf5deb3
# define COLOR_TOP		0xff5050
# define COLOR_HOLLOW	0x1da1e2

# define ERR				0
# define ERR_AND_DEL_ONE	1
# define ERR_AND_DEL_TWO	2
# define CLOSE				3

enum	e_mouse_events{LEFT_MB = 1, RIGHT_MB, MIDDLE_MB, DOWN_WHEEL, UP_WHEEL};
enum	e_keys_events{X_UP = 84, X_DOWN = 91, Y_UP = 88, Y_DOWN = 86, Z_UP = 89,
	Z_DOWN = 92, ISO = 34, PARALLEL = 35, ESC = 53, HEY = 36};

extern int		g_length;
extern int		g_height;
extern int		g_max;
extern int		g_min;

extern int		g_lowland;
extern int		g_hill;
extern int		g_top;

typedef struct	s_coord
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_coord;

typedef struct	s_mapstate
{
	int		scale;
	int		x_grab;
	int		y_grab;
	int		x_move;
	int		y_move;
	float	y_angle;
	float	x_angle;
	float	z_angle;
}				t_mapstate;

typedef struct	s_image
{
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		*data;
}				t_image;

typedef	struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_coord		**matrix;
	t_mapstate	*map;
	t_image		*image;
	int			screen_width;
	int			screen_height;
	int			grab;
}				t_fdf;
/*
** INITIALIZATION AND FREEING
*/
t_coord			**get_coords(int fd);
t_coord			**strdup_matrix(t_coord **matrix);
t_fdf			*init(int fd);
int				valid_check(char *path, char *line);
void			finish_him(void ***to_del, int flag);
int				hex_to_dec(const char *src);
int				ft_advanced_atoi(char *str, char c);
/*
** MAP MANIPULATIONS
*/
void			scale_map(t_coord **matrix, void *param);
void			move_map(t_coord **m, int x_move, int y_move);
void			x_rotation(t_coord **m, float angle);
void			y_rotation(t_coord **m, float angle);
void			z_rotation(t_coord **m, float angle);
void			iso_projection(t_coord **matrix);
/*
** EVENT MANIPULATION
*/
void			angle_changer(int x, int y, void *param);
void			grab_and_move(int x, int y, void *param);
void			event_manip(int x, int y, int flag, void *param);
int				mouse_press(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
int				key_press(int keycode, void *param);
int				ft_close(void *param);
void			map_changer(int x, int y, int flag, void *param);
/*
**	DRAWING
*/
void			ft_paint_matrix(t_coord **matrix, void *param);
void			draw_line(t_coord coord1, t_coord coord2, void *param);
int				color_intens(int color, float k);
int				get_color(t_coord current, t_coord start, t_coord end, int f);
void			gradient_coord(t_coord **matr, int start_color, int end_color);
int				get_light(int start, int end, double percentage);
double			percent(int start, int end, int current);
int				gradient_color(t_coord **matrix);
#endif
