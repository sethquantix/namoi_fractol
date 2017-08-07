/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 10:17:52 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 10:17:59 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(int x, int y, t_env *e)
{
	int		*button;
	float	z;

	button = e->mouse.button;
	if (button[1] || button[2] || button[4] || button[5])
	{
		z = (float)button[1] * ZOOM + (float)button[2] / (float)ZOOM;
		z += (float)button[4] * ZOOM_M + (float)button[5] / (float)ZOOM_M;
		new_coord(e, x, y, z);
	}
}

void	julia_move(int x, int y, t_env *e)
{
	if ((e->fractal != JULIA && e->fractal != QUAT))
		return ;
	if (e->fractal == JULIA)
	{
		e->data.jc.x += (e->m_old.x - x) * e->j_var.x;
		e->data.jc.y += (e->m_old.y - y) * e->j_var.y;
	}
	else
		e->data.c = quat(e->data.c, float2((e->m_old.x - x) * e->j_var.x,
			(e->m_old.y - y) * e->j_var.y), e->dir);
}

void	move(int x, int y, t_env *e)
{
	move_coord(e, e->m_old.x - x, -y + e->m_old.y);
}
