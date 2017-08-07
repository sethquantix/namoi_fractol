/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 01:13:41 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 07:42:49 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			hsv(float h, float s, float v)
{
	int			ti;
	cl_float4	f;
	cl_int3		rgb;

	ti = (int)(h / 60) % 6;
	f.x = h / 60.0 - (int)(h / 60);
	f.y = v * (1.0 - s);
	f.z = v * (1.0 - f.x * s);
	f.w = v * (1.0 - (1.0 - f.x) * s);
	if (ti == 0)
		rgb = int3(255 * v, 255 * f.w, 255 * f.y);
	if (ti == 1)
		rgb = int3(255 * f.z, 255 * v, 255 * f.y);
	if (ti == 2)
		rgb = int3(255 * f.y, 255 * v, 255 * f.w);
	if (ti == 3)
		rgb = int3(255 * f.y, 255 * f.z, 255 * v);
	if (ti == 4)
		rgb = int3(255 * f.w, 255 * f.y, 255 * v);
	if (ti == 5)
		rgb = int3(255 * v, 255 * f.y, 255 * f.z);
	return ((rgb.x << 16) + (rgb.y << 8) + rgb.z);
}

void		plot_circle(t_env *e, cl_int2 center, cl_int2 pos, cl_float3 col)
{
	float		r;
	cl_float2	p;

	p = float2(pos.x - center.x, center.y - pos.y);
	r = fmod(atan2(p.y, p.x) * 180.0 / M_PI + 180 + 90.0 + col.x, 360.0);
	((int *)e->buf)[pos.x + WIDTH * pos.y] = hsv(r, 1.0, 1.0);
}

void		plot_triangle(t_env *e, cl_int2 *p, cl_int2 pos, cl_float3 col)
{
	float	a;
	float	s;
	float	t;

	a = area(p[0], p[1], p[2]);
	s = 1 / (2 * a) * (p[0].y * p[2].x - p[0].x * p[2].y +
		(p[2].y - p[0].y) * pos.x + (p[0].x - p[2].x) * pos.y);
	t = 1 / (2 * a) * (p[0].x * p[1].y - p[0].y * p[1].x +
		(p[0].y - p[1].y) * pos.x + (p[1].x - p[0].x) * pos.y);
	if (s < 0 || t < 0 || (1.0 - s - t) < 0)
		return ;
	((int *)e->buf)[pos.x + WIDTH * pos.y] = hsv(col.x, 1 - t, 1 - s);
}

cl_float2	sv(cl_int2 pos, cl_int2 *p)
{
	float	a;
	float	s;
	float	t;

	a = area(p[0], p[1], p[2]);
	s = 1 / (2 * a) * (p[0].y * p[2].x - p[0].x * p[2].y +
		(p[2].y - p[0].y) * pos.x + (p[0].x - p[2].x) * pos.y);
	t = 1 / (2 * a) * (p[0].x * p[1].y - p[0].y * p[1].x +
		(p[0].y - p[1].y) * pos.x + (p[1].x - p[0].x) * pos.y);
	if (s < 0 || t < 0 || (1.0 - s - t) < 0)
		return (float2(-1, -1));
	return (float2(1 - t, 1 - s));
}

int			hue(t_env *e, cl_int2 p, int col)
{
	cl_float2	f;
	float		rad;
	float		h;

	if (col == 0)
		h = e->data.c1.x;
	else
		h = e->data.c2.x;
	f = float2(p.x - e->centers[col].x, e->centers[col].y - p.y);
	rad = fmod(atan2(f.y, f.x) * 180.0 / M_PI + 270.0 + h, 360.0);
	if (col == 0)
		e->data.c1.x = rad;
	else
		e->data.c2.x = rad;
	return (1);
}
