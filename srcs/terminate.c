/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 18:00:28 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/07 09:18:51 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	release(t_env *e)
{
	int		ker;

	if (e->context)
		clReleaseContext(e->context);
	if (e->queue)
		clReleaseCommandQueue(e->queue);
	if (e->program)
		clReleaseProgram(e->program);
	if (e->cl_buffer)
		clReleaseMemObject(e->cl_buffer);
	if (e->cl_data)
		clReleaseMemObject(e->cl_buffer);
	if (e->step)
		clReleaseMemObject(e->step);
	ker = -1;
	while (++ker < FRACTALS)
		if (e->kernels[ker])
			clReleaseKernel(e->kernels[ker]);
}

void	die(char *s, t_env *e, int exit_code)
{
	ft_printf("%s ! %s\n", exit_code == EXIT_FAILURE ?
		"FAILURE" : "SUCCESS", s == NULL ? "Bad arguments provided. \
		\nRequired one of :\n==> (Mandel)brot\n==> Julia\n==> Burning \
		\n==> Sponge\n==> (Mandel)bulb\n==> (Mandel)box\n==> Quat(ernion) \
		\n==> Buddha(brot)\n\nThose are case insensitive.\n" : s);
	if (e)
	{
		if (e->win && e->mlx)
			mlx_destroy_window(e->mlx, e->win);
		if (e->img && e->mlx)
			mlx_destroy_image(e->mlx, e->img);
		if (e->k_size)
			free(e->k_size);
		release(e);
	}
	exit(exit_code);
}

int		k_exit(int keycode, t_env *e)
{
	(void)keycode;
	die("!\nCleaning code...\nPurging...\nDeleting traces...\
	\nTaking care of witnesses", e, EXIT_SUCCESS);
	return (0);
}
