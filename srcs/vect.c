/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 02:59:28 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/07 09:08:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

cl_int2		int2(int x, int y)
{
	cl_int2		p;

	p.x = x;
	p.y = y;
	return (p);
}

cl_int3		int3(int x, int y, int z)
{
	cl_int3		v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

cl_float2	float2(float x, float y)
{
	cl_float2	p;

	p.x = x;
	p.y = y;
	return (p);
}

cl_float3	float3(float x, float y, float z)
{
	cl_float3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

cl_int2		rot(cl_int2 p, cl_int2 center, float rad)
{
	cl_int2		r;
	cl_float2	t;

	t = float2(p.x - center.x, p.y - center.y);
	r = int2(center.x + t.x * cos(rad) - t.y * sin(rad),
		center.y + t.x * sin(rad) + t.y * cos(rad));
	return (r);
}
