/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:53:57 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 20:09:23 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int g_height;
int g_length;

static void	close_flag(void *param)
{
	mlx_destroy_image(MLX_PTR, IMG_PTR);
	mlx_destroy_window(MLX_PTR, WIN_PTR);
	ft_memdel((void**)&IMG);
	ft_memdel((void**)&MAP);
	ft_del_twodem_arr((void***)&MATRIX);
	ft_memdel(MLX_PTR);
	ft_memdel(&param);
	exit(0);
}

void		finish_him(void ***to_del, int flag)
{
	void *param;

	param = to_del;
	if (flag == ERR)
	{
		ft_putstr("error\n");
		exit(0);
	}
	if (flag == ERR_AND_DEL_ONE)
	{
		ft_memdel(*to_del);
		ft_putstr("error\n");
		exit(0);
	}
	else if (flag == ERR_AND_DEL_TWO)
	{
		ft_del_twodem_arr(to_del);
		ft_putstr("error\n");
		exit(0);
	}
	else if (flag == CLOSE)
		close_flag(param);
}

int			find_length(char *line)
{
	int		j;
	char	**arr;

	j = 0;
	arr = ft_strsplit(line, ' ');
	while (*(arr + j))
		j++;
	ft_del_twodem_arr((void***)&arr);
	return (j);
}

int			valid_check(char *path, char *line)
{
	int			fd;
	int			i;
	int			j;
	int			len;
	int			flag;

	i = 0;
	j = 0;
	flag = 0;
	if ((fd = open(path, O_RDONLY)) == -1)
		finish_him(NULL, ERR);
	while (get_next_line(fd, &line))
	{
		if (!flag && (len = find_length(line)))
			flag = -1;
		if ((g_length = find_length(line)) != len)
			finish_him(NULL, ERR);
		ft_strdel(&line);
		i++;
	}
	g_height = i;
	close(fd);
	return (0);
}
