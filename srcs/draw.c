/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 19:41:25 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 07:40:26 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	rand_colors(t_env *e)
{
	int	r;
	int	k;

	k = rand() % 100;
	while (k--)
		r = rand();
	e->data.c1.x = (rand() % 36000) / 100.0;
	e->data.c1.y = (rand() % 1000) / 1000.0;
	e->data.c1.z = (rand() % 1000) / 1000.0;
	e->data.c2.x = (rand() % 36000) / 100.0;
	e->data.c2.y = (rand() % 1000) / 1000.0;
	e->data.c2.z = (rand() % 1000) / 1000.0;
	e->rand = 0;
	e->data.amb.x = (rand() % 1000) / 1000.0;
	e->data.amb.y = (rand() % 1000) / 1000.0;
	e->data.amb.z = (rand() % 1000) / 1000.0;
	e->data.diff.x = (rand() % 1000) / 1000.0;
	e->data.diff.y = (rand() % 1000) / 1000.0;
	e->data.diff.z = (rand() % 1000) / 1000.0;
	e->data.spec.x = (rand() % 1000) / 1000.0;
	e->data.spec.y = (rand() % 1000) / 1000.0;
	e->data.spec.z = (rand() % 1000) / 1000.0;
	e->data.shine = (rand() % 10000) / 100.0;
	e->rand = 0;
}

void	kernel_run(t_env *e)
{
	clEnqueueNDRangeKernel(e->queue, e->kernels[e->fractal], 2, NULL,
		e->k_size->global, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(e->queue, e->cl_buffer, CL_TRUE, 0,
		sizeof(int) * WIDTH * HEIGHT, (int *)e->buf, 0, NULL, NULL);
	if (e->fractal >= MENGER)
		clEnqueueReadBuffer(e->queue, e->step, CL_TRUE, 0, sizeof(float),
		&(e->data.step), 0, NULL, NULL);
	clFinish(e->queue);
}

void	run(t_env *e)
{
	rotate_corners(e);
	clEnqueueWriteBuffer(e->queue, e->cl_data, CL_TRUE, 0, sizeof(t_data),
		&e->data, 0, NULL, NULL);
	clFinish(e->queue);
	kernel_run(e);
}

void	info(t_env *e, int i, int j)
{
	char			*s;
	static char		*states[3] = {"Zoom on", "Move on", "Changing set"};

	ft_sprintf(&s, "%s render | iteration count at %d | %s\n",
		"GPU", e->data.max_iter, states[(int)e->state]);
	while (++j < 30)
	{
		i = -1;
		while (++i < WIDTH)
			((int *)e->buf)[i + j * WIDTH] = 0;
	}
	mlx_string_put(e->mlx, e->win, 0, 0, 0xFF00, s);
}

void	draw(t_env *e)
{
	if (e->rand)
		rand_colors(e);
	if (e->fractal != BUDDHA)
		run(e);
	else
		buddha(e, &e->data);
	if (e->colors && !e->hook_mode)
		menu(e);
	if (e->colors && e->hook_mode)
		draw_boxes(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	if (e->info)
		info(e, -1, -1);
}
