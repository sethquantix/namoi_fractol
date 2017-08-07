/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 21:10:57 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 18:04:15 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	geometry(t_env *e)
{
	int			i;

	i = -1;
	create_boxes(e);
	e->centers[0] = int2((float)WIDTH * 0.875, (float)WIDTH * 0.125);
	e->centers[1] = int2((float)WIDTH * 0.875, HEIGHT - (float)WIDTH * 0.125);
	e->rads = int2(0.5 * (float)e->centers[0].y, 0.6 * (float)e->centers[0].y);
	while (++i < 2)
	{
		e->p[i][0] = int2(e->centers[i].x, e->centers[i].y -
			0.9 * (float)e->rads.x);
		e->p[i][1] = rot(e->p[i][0], e->centers[i], (4.0 * M_PI) / 3.0);
		e->p[i][2] = rot(e->p[i][0], e->centers[i], (2.0 * M_PI) / 3.0);
	}
	e->data.cam = float3(0, 0, -7.0f);
	e->data.step = 0.0001;
	rotate_corners(e);
}

void	set_data(t_env *e)
{
	geometry(e);
	rand_colors(e);
	e->hd = 1;
	e->data.width = WIDTH;
	e->data.height = HEIGHT;
	e->data.min_x = -2;
	e->data.max_x = 2;
	e->data.min_y = e->data.min_x * (float)HEIGHT / (float)WIDTH;
	e->data.max_y = e->data.max_x * (float)HEIGHT / (float)WIDTH;
	e->data.max_iter = 100;
	e->j_var.x = J_VARX;
	e->j_var.y = J_VARY;
	set_values(e->boxes);
	m_set_ident3(e->data.mat);
	if ((e->mats = ft_memalloc(sizeof(cl_float3 *) * 3)) == NULL)
		die("Not enough memory", e, EXIT_FAILURE);
	alloc_mats(e);
	m_set_rot((cl_float3 **)e->mats);
}

void	set(t_env *e)
{
	if ((e->k_size = ft_memalloc(sizeof(t_size))) == NULL)
		die("malloc failed : sizes alloc.", e, EXIT_FAILURE);
	if ((e->mlx = mlx_init()) == NULL)
		die("couldnt init mlx. That means trouble.", e, EXIT_FAILURE);
	if ((e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "Fract'ol")) == NULL)
		die("Couldnt open a window. Now That's bad.", e, EXIT_FAILURE);
	if ((e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT)) == NULL)
		die("Couldnt create the buffer image. Not gonna work, sadly.", e,
			EXIT_FAILURE);
	e->buf = mlx_get_data_addr(e->img, &e->bpp, &e->lsz, &e->end);
	if (e->buf == NULL)
		die("No buffer for image. That really shouldnt have happened.", e,
			EXIT_FAILURE);
	set_data(e);
	opencl_init(e);
}

int		parse(t_env *e, int ac, char **av)
{
	int				i;
	const t_fract	names[14] = {{"mandelbrot", 0}, {"brot", 0}, {"julia", 1},
		{"burning", 2}, {"sponge", 3}, {"mandelbulb", 4}, {"bulb", 4},
		{"mandelbox", 5}, {"box", 5}, {"quaternion", 6}, {"quat", 6},
		{"buddhabrot", 7}, {"buddha", 7}};

	i = 0;
	if (!ac || ac > 1)
		die(NULL, e, EXIT_FAILURE);
	ft_strtolower(*av);
	while (i < 14)
		if (ft_strcmp(names[i].name, *av) == 0)
			return (names[i].fract);
		else
			i++;
	die(NULL, e, EXIT_FAILURE);
	return (-1);
}

int		main(int ac, char **av)
{
	t_env	e;

	srand(time(NULL));
	ft_bzero(&e, sizeof(t_env));
	e.fractal = parse(&e, ac - 1, av + 1);
	set(&e);
	mlx_hook(e.win, KeyPress, KeyPressMask, &key_hook, &e);
	mlx_hook(e.win, KeyRelease, KeyReleaseMask, &key_release_hook, &e);
	mlx_hook(e.win, ButtonPress, ButtonPressMask, &mouse_hook, &e);
	mlx_hook(e.win, ButtonRelease, ButtonReleaseMask, &mouse_release_hook, &e);
	mlx_hook(e.win, MotionNotify, PointerMotionMask, &mouse_free_hook, &e);
	mlx_loop_hook(e.mlx, &loop_hook, &e);
	init_keys(&e);
	draw(&e);
	mlx_loop(e.mlx);
	die("all is done, good job everyone. Time to clean everything up !", &e,
		EXIT_SUCCESS);
	(void)ac;
	(void)av;
	return (0);
}
