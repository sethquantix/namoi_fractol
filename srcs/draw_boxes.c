/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_boxes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 09:12:49 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 09:12:51 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_box	*intersect(int x, int y, t_list *boxes)
{
	t_box	*box;

	while (boxes)
	{
		box = TBOX(boxes->content);
		if (x > box->x && x < box->x + box->sx && y > box->y
			&& y < box->y + box->sy)
			return (box);
		boxes = boxes->next;
	}
	return (NULL);
}

void	draw_box(t_box *box, t_env *e, int i, int c0)
{
	int		x;
	int		y;
	int		c;

	x = box->x;
	while (x < box->x + box->sx)
	{
		y = box->y;
		c = (int)(255.0 * (float)(x - box->x) / (float)box->sx);
		c = c0 + (i == -1 ? (c << 16) + (c << 8) + c :
			(i == 0) * (c << 16) + (i == 1) * (c << 8) + (i == 2) * c);
		while (y < box->y + box->sy)
		{
			((int *)e->buf)[x + y * WIDTH] = c;
			y++;
		}
		x++;
	}
}

void	draw_col_boxes(t_box *boxes[3][3], t_env *e)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			c = (((j != 0) * (int)(255.0 * boxes[i][0]->pos)) << 16) +
				(((j != 1) * (int)(255.0 * boxes[i][1]->pos)) << 8) +
				(((j != 2) * (int)(255.0 * boxes[i][2]->pos)));
			draw_box(boxes[i][j], e, j, c);
			j++;
		}
		i++;
	}
}

void	draw_boxes(t_env *e)
{
	static t_box	*col_boxes[3][3] = {{NULL}};
	t_list			*boxes;

	boxes = e->boxes;
	if (!col_boxes[0][0])
	{
		col_boxes[0][0] = get_box(boxes, &e->data.amb.x);
		col_boxes[0][1] = get_box(boxes, &e->data.amb.y);
		col_boxes[0][2] = get_box(boxes, &e->data.amb.z);
		col_boxes[1][0] = get_box(boxes, &e->data.diff.x);
		col_boxes[1][1] = get_box(boxes, &e->data.diff.y);
		col_boxes[1][2] = get_box(boxes, &e->data.diff.z);
		col_boxes[2][0] = get_box(boxes, &e->data.spec.x);
		col_boxes[2][1] = get_box(boxes, &e->data.spec.y);
		col_boxes[2][2] = get_box(boxes, &e->data.spec.z);
	}
	draw_col_boxes(col_boxes, e);
	while (boxes)
	{
		if (TBOX(boxes->content)->type && (TBOX(boxes->content)->cond ==
			e->fractal || TBOX(boxes->content)->cond == -1))
			draw_box(TBOX(boxes->content), e, -1, 0);
		boxes = boxes->next;
	}
}
