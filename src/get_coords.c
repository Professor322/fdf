/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 16:05:48 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 20:47:21 by jziemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		g_max = 0;
int		g_min = 0;

void		ft_max_min(int z)
{
	if (g_max < z)
		g_max = z;
	else if (z < 0 && g_min > z)
		g_min = z;
}

int			line_parse(char *line, t_coord **matrix, int y)
{
	char	**parse_arr;
	int		x;
	char	*color_check;

	if (!(parse_arr = ft_strsplit(line, ' ')))
		finish_him((void***)matrix, ERR_AND_DEL_TWO);
	x = -1;
	while (*(parse_arr + ++x))
	{
		(*(matrix + y) + x)->z = ft_advanced_atoi(*(parse_arr + x), ',');
		(*(matrix + y) + x)->y = y - g_height / 2;
		(*(matrix + y) + x)->x = x - g_length / 2;
		if ((color_check = ft_strchr(*(parse_arr + x), ',')))
			(*(matrix + y) + x)->color = hex_to_dec(++color_check);
		else if ((*(matrix + y) + x)->z)
			ft_max_min((*(matrix + y) + x)->z);
		else
			(*(matrix + y) + x)->color = g_lowland;
	}
	ft_del_twodem_arr((void***)&parse_arr);
	return (0);
}

t_coord		**get_coords(int fd)
{
	char		*line;
	t_coord		**matrix;
	int			i;

	line = NULL;
	if (!(matrix = (t_coord**)malloc(sizeof(t_coord*) * (g_height + 1))))
		finish_him(NULL, ERR);
	i = 0;
	while (i < g_height)
		if (!(*(matrix + i++) = (t_coord*)malloc(sizeof(t_coord) * g_length)))
			finish_him((void***)matrix, ERR_AND_DEL_TWO);
	*(matrix + i) = NULL;
	i = -1;
	while (get_next_line(fd, &line))
	{
		line_parse(line, matrix, ++i);
		ft_strdel(&line);
	}
	gradient_coord(matrix, g_hill, g_top);
	return (matrix);
}
