/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 10:17:55 by cchaumar          #+#    #+#             */
/*   Updated: 2016/06/26 22:05:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	m_set_ident3(cl_float3 *m)
{
	int		j;

	j = -1;
	while (++j < 3)
	{
		m[j].x = j == 0 ? 1 : 0;
		m[j].y = j == 1 ? 1 : 0;
		m[j].z = j == 2 ? 1 : 0;
	}
}

void	m_set(cl_float3 *m1, cl_float3 *m2)
{
	int		i;

	i = -1;
	while (++i < 3)
		m1[i] = float3(m2[i].x, m2[i].y, m2[i].z);
}

void	m_mult3(cl_float3 *m1, cl_float3 *m2)
{
	cl_float3	m[3];
	int			i;

	m_set(m, m1);
	i = -1;
	while (++i < 3)
	{
		m1[i].x = dot3(m[i], float3(m2[0].x, m2[1].x, m2[2].x));
		m1[i].y = dot3(m[i], float3(m2[0].y, m2[1].y, m2[2].y));
		m1[i].z = dot3(m[i], float3(m2[0].z, m2[1].z, m2[2].z));
	}
}

void	m_set_rot(cl_float3 **mats)
{
	mats[0][0] = (float3)(1, 0, 0);
	mats[0][1] = (float3)(0, cos(RAD_ROT), -sin(RAD_ROT));
	mats[0][2] = (float3)(0, sin(RAD_ROT), cos(RAD_ROT));
	mats[1][0] = (float3)(cos(RAD_ROT), 0, sin(RAD_ROT));
	mats[1][1] = (float3)(0, 1, 0);
	mats[1][2] = (float3)(-sin(RAD_ROT), 0, cos(RAD_ROT));
	mats[2][0] = (float3)(cos(RAD_ROT), -sin(RAD_ROT), 0);
	mats[2][1] = (float3)(sin(RAD_ROT), cos(RAD_ROT), 0);
	mats[2][2] = (float3)(0, 0, 1);
}
