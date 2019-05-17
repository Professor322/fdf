/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 17:01:25 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 19:14:46 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord		**strdup_matrix(t_coord **matrix)
{
	t_coord **n_mtrx;
	int		i;
	int		j;

	if (!(n_mtrx = (t_coord**)malloc(sizeof(t_coord*) * (g_height + 1))))
		finish_him(NULL, ERR);
	i = 0;
	while (i < g_height)
		if (!(*(n_mtrx + i++) = (t_coord*)malloc(sizeof(t_coord) * g_length)))
			finish_him((void***)&matrix, ERR_AND_DEL_TWO);
	*(n_mtrx + i) = NULL;
	i = -1;
	while (++i < g_height)
	{
		j = -1;
		while (++j < g_length)
		{
			(*(n_mtrx + i) + j)->x = (*(matrix + i) + j)->x;
			(*(n_mtrx + i) + j)->y = (*(matrix + i) + j)->y;
			(*(n_mtrx + i) + j)->z = (*(matrix + i) + j)->z;
			(*(n_mtrx + i) + j)->color = (*(matrix + i) + j)->color;
		}
	}
	return (n_mtrx);
}
