/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 10:48:08 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/07 09:28:27 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

cl_float3	v_mat_mult3(cl_float3 v, cl_float3 *m)
{
	return (float3(dot3(v, m[0]), dot3(v, m[1]), dot3(v, m[2])));
}

void		rotate_corners(t_env *e)
{
	static cl_float2	d;
	int					i;

	i = -1;
	if (d.x == 0)
		d = float2(tan(M_PI / 6.0), tan(M_PI / 6.0) *
		(float)HEIGHT / (float)WIDTH);
	e->data.corners[0] = float3(-d.x, d.y, 1);
	e->data.corners[1] = float3(d.x, d.y, 1);
	e->data.corners[2] = float3(-d.x, -d.y, 1);
	while (++i < 3)
		e->data.corners[i] = v_mat_mult3(e->data.corners[i], e->data.mat);
}

int			rotate_cam(int keycode, t_env *e)
{
	int			dir;
	int			axis;
	cl_float3	mat[3];
	int			i;

	dir = (keycode == 0x7c || keycode == 0x7e || keycode == 0x7) -
		(keycode == 0x7b || keycode == 0x7d || keycode == 0x6);
	axis = (keycode == 0x7c || keycode == 0x7b) + 2 * (keycode == 0x6 ||
		keycode == 0x7);
	i = -1;
	while (++i < 3)
		mat[i] = float3((i == 0 ? 1 : dir) * e->mats[axis][i].x,
			(i == 1 ? 1 : dir) * e->mats[axis][i].y,
			(i == 2 ? 1 : dir) * e->mats[axis][i].z);
	m_mult3(e->data.mat, mat);
	return (0);
}

int			move_cam(int keycode, t_env *e)
{
	cl_int3		t;
	cl_float3	v;

	t = int3(-(keycode == 0x0) + (keycode == 0x2), -(keycode == 0x1) +
		(keycode == 0xd), -(keycode == 0xc) + (keycode == 0xe));
	v = float3((float)t.x * e->data.step, (float)t.y * e->data.step,
		(float)t.z * e->data.step);
	v = v_mat_mult3(v, e->data.mat);
	e->data.cam = float3(e->data.cam.x + v.x, e->data.cam.y + v.y,
		e->data.cam.z + v.z);
	return (0);
}
