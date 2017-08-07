/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boxes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 15:24:49 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/07 09:22:20 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_list	*add_box(float *p, float min, float max, int type)
{
	t_list	*node;
	t_box	box;

	box.p = p;
	box.min = min;
	box.max = max;
	box.type = type;
	box.pos = 0.5f;
	box.cond = -1;
	node = ft_lstnew(&box, sizeof(t_box));
	return (node);
}

void	get_values(t_list *boxes)
{
	t_box	*box;

	while (boxes)
	{
		box = TBOX(boxes->content);
		box->pos = (*(box->p) - box->min) / (box->max - box->min);
		boxes = boxes->next;
	}
}

void	set_values(t_list *boxes)
{
	t_box	*box;

	while (boxes)
	{
		box = TBOX(boxes->content);
		*(box->p) = box->pos * (box->max - box->min) + box->min;
		boxes = boxes->next;
	}
}

t_box	*get_box(t_list *boxes, float *addr)
{
	while (boxes)
		if (TBOX(boxes->content)->p == addr)
			return (TBOX(boxes->content));
		else
			boxes = boxes->next;
	return (NULL);
}

void	draw_selector(cl_int2 pos, int height, int col, t_env *e)
{
	int		u;
	int		v;

	(void)height;
	v = -6;
	while (++v)
	{
		u = v - 1;
		while (++u <= 0)
		{
			((int*)e->buf)[pos.x + u + (pos.y + v) * WIDTH] = col;
			((int*)e->buf)[pos.x - u + (pos.y + v) * WIDTH] = col;
		}
	}
}
