/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 16:36:11 by cchaumar          #+#    #+#             */
/*   Updated: 2016/08/20 16:36:50 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	layout_boxes(t_env *e)
{
	t_list	*root;
	float	x;
	float	y;
	float	sx;
	float	sy;

	x = WIDTH * 0.8;
	sx = WIDTH * 0.15;
	sy = MIN((float)HEIGHT / (float)(1 + ft_lstsize(e->boxes)), sx * 0.10);
	y = sy / 2.0;
	root = e->boxes;
	while (root)
	{
		TBOX(root->content)->x = (int)x;
		TBOX(root->content)->y = (int)y;
		TBOX(root->content)->sx = (int)sx;
		TBOX(root->content)->sy = (int)(sy * 0.8);
		y += sy;
		root = root->next;
	}
}

void	create_boxes(t_env *e)
{
	ft_lstadd(&e->boxes, add_box(&e->data.rads.y, 0, 10, 1));
	TBOX(e->boxes->content)->cond = BOX;
	ft_lstadd(&e->boxes, add_box(&e->data.rads.x, 0, 4, 1));
	TBOX(e->boxes->content)->cond = BOX;
	ft_lstadd(&e->boxes, add_box(&e->data.box_scale, -4, 4, 1));
	TBOX(e->boxes->content)->cond = BOX;
	ft_lstadd(&e->boxes, add_box(&e->data.shine, 0, 100, 1));
	ft_lstadd(&e->boxes, add_box(&e->data.spec.z, 0, 1, 0));
	ft_lstadd(&e->boxes, add_box(&e->data.spec.y, 0, 1, 0));
	ft_lstadd(&e->boxes, add_box(&e->data.spec.x, 0, 1, 0));
	ft_lstadd(&e->boxes, add_box(&e->data.diff.z, 0, 1, 0));
	ft_lstadd(&e->boxes, add_box(&e->data.diff.y, 0, 1, 0));
	ft_lstadd(&e->boxes, add_box(&e->data.diff.x, 0, 1, 0));
	ft_lstadd(&e->boxes, add_box(&e->data.amb.z, 0, 1, 0));
	ft_lstadd(&e->boxes, add_box(&e->data.amb.y, 0, 1, 0));
	ft_lstadd(&e->boxes, add_box(&e->data.amb.x, 0, 1, 0));
	layout_boxes(e);
}

void	alloc_mats(t_env *e)
{
	int		i;

	i = -1;
	while (++i < 3)
		if ((e->mats[i] = ft_memalloc(sizeof(cl_float3) * 3)) == NULL)
			die("Not enough memory", e, EXIT_FAILURE);
}

int		toggle_val(int keycode, t_env *e)
{
	static t_val	match[7] = {{-1, NULL}};
	int				i;

	if (match[0].keycode == -1)
	{
		match[0] = (t_val){0x03, &e->julia_mode};
		match[1] = (t_val){0x2f, &e->colors};
		match[2] = (t_val){0x2c, &e->info};
		match[3] = (t_val){0x08, &e->dir};
		match[4] = (t_val){0x32, &e->mode};
		match[5] = (t_val){0x0f, &e->rand};
	}
	i = 0;
	key_release_hook(keycode, e);
	while (match[i].keycode != -1)
		if (match[i].keycode == keycode)
			return ((*(match[i].val) ^= 1));
		else
			i++;
	return (-1);
}

void	init_keys(t_env *e)
{
	static int		keys[NKEYS] = {0x35, 0x0, 0x2, 0x1, 0xD, 0xC, 0xE,
		0x7E, 0x7D, 0x7B, 0x7C, 0x06, 0x07, 0x31, 0x45, 0x4E, 0xf,
		0x03, 0x2f, 0x2c, 0x08, 0x32, 0x4, 0x5, 0x12, 0x13, 0x14, 0x15,
		0x17, 0x16, 0x1a, 0x1c};
	static int		(*funcs[NKEYS])(int, t_env *) = {k_exit, move_cam,
		move_cam, move_cam, move_cam, move_cam, move_cam,
		rotate_cam, rotate_cam, rotate_cam, rotate_cam, rotate_cam,
		rotate_cam, space, iter, iter, toggle_val, toggle_val,
		toggle_val, toggle_val, toggle_val, toggle_val, space, space,
		space, space, space, space, space, space, space, space};
	int				i;

	i = -1;
	if ((e->keys = ft_memalloc(sizeof(t_key) * NKEYS)) == NULL)
		die("out of memory (lol)", e, EXIT_FAILURE);
	while (++i < NKEYS)
		e->keys[i] = (t_key){keys[i], 0, funcs[i]};
}
