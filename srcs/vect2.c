/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 06:08:51 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/07 09:09:12 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

cl_double4	double4(double x, double y, double z, double w)
{
	cl_double4	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return (v);
}

cl_double2	double2(double x, double y)
{
	cl_double2	v;

	v.x = x;
	v.y = y;
	return (v);
}

cl_float4	float4(float x, float y, float z, float w)
{
	cl_float4	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return (v);
}

cl_float4	quat(cl_float4 c, cl_float2 mv, int dir)
{
	return (float4(c.x + (!dir) * mv.x, c.y + (!dir) * mv.y, c.z +
		dir * mv.x, c.w + dir * mv.y));
}
