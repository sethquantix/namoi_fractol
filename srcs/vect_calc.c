/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 04:42:33 by cchaumar          #+#    #+#             */
/*   Updated: 2016/06/17 10:32:14 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

float	area(cl_int2 p1, cl_int2 p2, cl_int2 p3)
{
	return (((float)(p2.x * p3.y - p2.y * p3.x + p1.y * (p3.x - p2.x) +
		p1.x * (p2.y - p3.y))) / 2.0);
}

float	dot3(cl_float3 v1, cl_float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
