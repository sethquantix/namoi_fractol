/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 19:41:25 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 07:44:39 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	dist(cl_int2 o, cl_int2 p)
{
	cl_float2	d;

	d.x = (float)p.x - (float)o.x;
	d.y = (float)p.y - (float)o.y;
	return (sqrt(d.x * d.x + d.y * d.y));
}

void	circle(cl_int2 center, cl_int2 rads, t_env *e, cl_float3 col)
{
	cl_int2		min;
	cl_int2		max;
	cl_int2		pos;

	min = int2(center.x - rads.y, center.y - rads.y);
	max = int2(center.x + rads.y, center.y + rads.y);
	pos.y = min.y - 1;
	while (++pos.y <= max.y)
	{
		pos.x = min.x - 1;
		while (++pos.x <= max.x)
			if (dist(center, pos) > rads.x && dist(center, pos) < rads.y)
				plot_circle(e, center, pos, col);
	}
}

void	triangle(cl_int2 center, cl_int2 *p, t_env *e, cl_float3 col)
{
	cl_int2		min;
	cl_int2		max;
	cl_int2		pos;

	min = int2(center.x - e->rads.y, center.y - e->rads.y);
	max = int2(center.x + e->rads.y, center.y + e->rads.y);
	pos.y = min.y - 1;
	while (++pos.y <= max.y)
	{
		pos.x = min.x - 1;
		while (++pos.x <= max.x)
			plot_triangle(e, p, pos, col);
	}
}

void	menu(t_env *e)
{
	if (e->hook_mode == 0)
	{
		circle(e->centers[0], e->rads, e, e->data.c1);
		circle(e->centers[1], e->rads, e, e->data.c2);
		triangle(e->centers[0], e->p[0], e, e->data.c1);
		triangle(e->centers[1], e->p[1], e, e->data.c2);
	}
}
