/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 19:01:54 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 07:43:32 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		iter(int keycode, t_env *e)
{
	int	dir;

	dir = keycode == 0x45 ? 1 : -1;
	e->data.max_iter = MAX(10, e->data.max_iter + dir * 10);
	return (0);
}

int		space(int keycode, t_env *e)
{
	static int		fractals[FRACTALS] = {0x12, 0x13, 0x14, 0x15, 0x17, 0x16,
		0x1a, 0x1c};
	int				i;

	key_release_hook(keycode, e);
	i = 0;
	while (i < FRACTALS)
		if (keycode == fractals[i])
			return (e->fractal = i);
		else
			i++;
	if (keycode == 0x4 && e->fractal == BUDDHA)
		e->hd = (e->hd % MAX_HD) + 1;
	if (keycode == 0x5 && e->fractal == BUDDHA)
		e->hd = 1;
	if (keycode == 0x31)
		e->state = (e->state + 1) % (2 + (e->fractal == JULIA));
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	int		i;

	i = 0;
	while (i < NKEYS)
		if (e->keys[i].keycode == keycode)
			return ((e->keys[i].pressed = 1));
		else
			i++;
	return (0);
}

int		key_release_hook(int keycode, t_env *e)
{
	int		i;

	i = 0;
	while (i < NKEYS)
		if (e->keys[i].keycode == keycode)
			return (e->keys[i].pressed = 0);
		else
			i++;
	return (0);
}
