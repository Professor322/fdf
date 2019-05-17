/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlegros <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 00:19:42 by vlegros           #+#    #+#             */
/*   Updated: 2019/03/20 19:07:57 by vlegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	hex_check(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else
		finish_him(NULL, ERR);
	return (-1);
}

static int	dec_check(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else
		finish_him(NULL, ERR);
	return (-1);
}

int			ft_advanced_atoi(char *src, char c)
{
	int result;
	int sign;

	result = 0;
	sign = 1;
	if (*src == '+' || *src == '-')
		*src++ == '-' ? (sign *= -1) : (sign *= 1);
	while (*src && *src != c)
		result = result * 10 + dec_check(*src++);
	return (result * sign);
}

int			hex_to_dec(const char *src)
{
	int result;

	result = 0;
	while (*src == 32 || (*src >= 9 && *src <= 13))
		src++;
	if (*src++ == '0' && (*src == 'x' || *src == 'X'))
		src++;
	else
		finish_him(NULL, ERR);
	while (*src && hex_check(*src) != -1)
		result = result * 16 + hex_check(*src++);
	return (result);
}
