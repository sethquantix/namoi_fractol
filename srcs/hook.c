/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 19:01:54 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 07:44:58 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colors_2d(int x, int y, t_env *e, int t)
{
	cl_int2		p;
	float		d;
	cl_float2	r;

	p = int2(x, y);
	d = dist(p, e->centers[0]);
	if (t && d > e->rads.x && d < e->rads.y)
		return (hue(e, p, 0));
	d = dist(p, e->centers[1]);
	if (t && d > e->rads.x && d < e->rads.y)
		return (hue(e, p, 1));
	if ((r = sv(p, e->p[0])).x != -1)
		return (set_sv(e, r, 0));
	if ((r = sv(p, e->p[1])).x != -1)
		return (set_sv(e, r, 1));
	return (0);
}

int		mouse_hook(int button, int x, int y, t_env *e)
{
	t_box	*box;

	e->mouse.button[button] = 1;
	if (e->hook_mode && e->mouse.button[1] && (box = intersect(x, y, e->boxes)))
	{
		e->mouse.box = box;
		box->pos = (x - box->x) / box->sx;
		*(box->p) = box->pos * (box->max - box->min) + box->min;
	}
	else if (!e->hook_mode && e->mouse.button[1] && colors_2d(x, y, e, 1))
		e->drag = 1;
	else if (e->state == 0 && (e->mouse.button[1] || e->mouse.button[2] ||
		e->mouse.button[4] || e->mouse.button[5]) && !colors_2d(x, y, e, 1))
		zoom(x, y, e);
	e->m_old = int2(x, y);
	return (0);
}

int		mouse_release_hook(int button, int x, int y, t_env *e)
{
	e->mouse.button[button] = 0;
	e->mouse.box = NULL;
	e->drag = 0;
	(void)x;
	(void)y;
	return (0);
}

int		mouse_free_hook(int x, int y, t_env *e)
{
	t_box		*box;

	box = e->mouse.box;
	if (box)
	{
		box->pos = (float)(x - box->x) / (float)box->sx;
		box->pos = box->pos > 1 ? 1 : box->pos;
		box->pos = box->pos < 0 ? 0 : box->pos;
		*(box->p) = box->min + (box->max - box->min) * box->pos;
	}
	else if (e->drag)
		return (colors_2d(x, y, e, 0));
	if (e->mouse.button[1] && e->state == 2)
		julia_move(x, y, e);
	if (e->mouse.button[1] && e->state == 1)
		move(x, y, e);
	if (!e->julia_mode && e->state != 2)
		julia_move(x, y, e);
	e->m_old = int2(x, y);
	return (0);
}

int		loop_hook(t_env *e)
{
	static int		fmods[FRACTALS] = {0, 0, 0, 1, 1, 1, 1, 0};
	int				i;
	int				t;

	i = 0;
	t = 0;
	e->hook_mode = fmods[e->fractal];
	while (i < NKEYS)
	{
		if (e->keys[i].pressed)
			t += e->keys[i].func(e->keys[i].keycode, e);
		i++;
	}
	e->state = e->state % (2 + (e->fractal == JULIA));
	draw(e);
	return (0);
}
