/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eve.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 00:39:04 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 07:41:14 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	new_coord(t_env *e, int x, int y, float zoom)
{
	float		size_x;
	float		size_y;
	float		new_x;
	float		new_y;

	size_x = e->data.max_x - e->data.min_x;
	size_y = e->data.max_y - e->data.min_y;
	new_x = (float)x * size_x / (float)WIDTH + e->data.min_x;
	new_y = (float)y * size_y / (float)HEIGHT + e->data.min_y;
	e->data.min_x = new_x - size_x * zoom / 2.0f;
	e->data.max_x = new_x + size_x * zoom / 2.0f;
	e->data.min_y = new_y - size_y * zoom / 2.0f;
	e->data.max_y = new_y + size_y * zoom / 2.0f;
}

void	move_coord(t_env *e, int x, int y)
{
	double		size_x;
	double		size_y;

	size_x = e->data.max_x - e->data.min_x;
	size_y = e->data.max_y - e->data.min_y;
	e->data.min_x += x * (float)size_x / (float)WIDTH;
	e->data.max_x += x * (float)size_x / (float)WIDTH;
	e->data.min_y += y * (float)size_y / (float)HEIGHT;
	e->data.max_y += y * (float)size_y / (float)HEIGHT;
}

int		set_sv(t_env *e, cl_float2 r, int col)
{
	if (col == 0)
		e->data.c1 = float3(e->data.c1.x, r.x, r.y);
	else
		e->data.c2 = float3(e->data.c2.x, r.x, r.y);
	return (1);
}
