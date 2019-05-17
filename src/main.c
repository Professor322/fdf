/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:40:16 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 23:47:08 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		g_lowland = COLOR_LOWLAND;
int		g_hill = COLOR_HILL;
int		g_top = COLOR_TOP;

void	ft_hook_loop(t_fdf *map)
{
	mlx_hook(map->win_ptr, 4, 0, mouse_press, map);
	mlx_hook(map->win_ptr, 5, 0, mouse_release, map);
	mlx_hook(map->win_ptr, 6, 0, mouse_move, map);
	mlx_hook(map->win_ptr, 2, 0, key_press, map);
	mlx_hook(map->win_ptr, 17, 0, ft_close, map);
	mlx_loop(map->mlx_ptr);
}

void	ft_usage(void)
{
	ft_putstr("usage: ./fdf source_file\t");
	ft_putstr("[color1 color2 color3]\n");
	exit(0);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_fdf	*map;
	char	*line;

	map = NULL;
	line = NULL;
	if (argc == 2 || argc == 5)
	{
		fd = open(argv[1], O_RDONLY);
		valid_check(argv[1], line);
		if (argc == 5)
		{
			g_lowland = hex_to_dec(argv[2]);
			g_hill = hex_to_dec(argv[3]);
			g_top = hex_to_dec(argv[4]);
		}
		map = init(fd);
		event_manip(0, 0, 0, map);
		close(fd);
		ft_hook_loop(map);
	}
	else
		ft_usage();
	return (0);
}
