/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddha.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 13:27:51 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 08:24:38 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

cl_double2			compute(cl_double2 z, cl_double2 c)
{
	cl_double2	r;

	r.x = c.x + z.x * z.x - z.y * z.y;
	r.y = c.y + 2 * z.x * z.y;
	return (r);
}

static int			sf_rec(cl_double4 z, t_data *data, int iter, int *map)
{
	cl_int2		p;
	cl_float2	zz;

	zz = float2(z.x * z.x - z.y * z.y + z.z, z.w + 2 * z.x * z.y);
	if (iter == 0 || (iter != data->max_iter && (fabs(zz.x - z.x) < EPS &&
		fabs(zz.y - z.y) < EPS)))
		return (0);
	if (z.x * z.x + z.y * z.y > 4.0)
		return (1);
	if (sf_rec(double4(zz.x, zz.y, z.z, z.w), data, iter - 1, map) == 1)
	{
		p = int2((z.x - data->min_x) / (data->max_x - data->min_x) *
			(float)WIDTH,
			(z.y - data->min_y) / (data->max_y - data->min_y) *
			(float)HEIGHT);
		if (p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT &&
			iter != data->max_iter)
			++map[p.y * WIDTH + p.x];
		return (1);
	}
	return (0);
}

static cl_float3	sf_col(cl_float3 c1, cl_float3 c2, int it, int m)
{
	cl_float3	c;

	c.x = (float)it * c2.x / (float)m + (float)(m - it) * c1.x / (float)m;
	c.y = (float)it * c2.y / (float)m + (float)(m - it) * c1.y / (float)m;
	c.z = (float)it * c2.z / (float)m + (float)(m - it) * c1.z / (float)m;
	return (c);
}

static void			sf_buddha(t_env *e, int *map, cl_float3 col)
{
	int		i;
	int		j;
	int		max;

	max = 0;
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
			max = MAX(max, map[j * WIDTH + i]);
	}
	j = -1;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			col = sf_col(e->data.c1, e->data.c2, map[j * WIDTH + i], max);
			((int *)e->buf)[i + j * WIDTH] = hsv(col.x, col.y, col.z);
		}
	}
}

void				buddha(t_env *e, t_data *data)
{
	int			i;
	int			j;
	int			*map;

	if ((map = ft_memalloc(sizeof(int) * HEIGHT * WIDTH)) == NULL)
		die("Not enough memory", e, EXIT_FAILURE);
	j = -1;
	while (++j < e->hd * HEIGHT)
	{
		i = -1;
		while (++i < e->hd * WIDTH)
			sf_rec(double4(0, 0, data->min_x +
			i * (data->max_x - data->min_x) / (double)(WIDTH * e->hd),
			data->min_y + j * (data->max_y - data->min_y) / (double)(HEIGHT *
			e->hd)), data, data->max_iter, map);
	}
	sf_buddha(e, map, float3(0, 0, 0));
	free(map);
}
