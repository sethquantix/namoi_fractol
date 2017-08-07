/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 03:57:32 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 07:01:23 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

inline void				format(t_field *f, t_data *d)
{
	size_t	l;
	size_t	a;
	char	*p;
	char	sign[2];

	a = f->flag & ALT ? 2 * !!(f->bools & BASE16) + !!(f->bools & BASE8) : 0;
	a += f->sign == -1 || (f->sign && !!(f->flag & (SPC + PLS)));
	l = f->size;
	l += a;
	sign[0] = f->flag & SPC ? ' ' : '+';
	l = MAX(l, (size_t)f->padd);
	while (d->pos + l - d->buff > (long)d->size)
		p_realloc(d);
	ft_memset(d->pos, f->flag & ZRO ? '0' : ' ', l);
	ft_memcpy(f->flag & (NEG | ZRO) ? d->pos : d->pos + l - f->size - a,
		f->spec & UXS ? "0X" : "0x", a);
	if (f->sign && a)
		ft_memcpy(f->flag & (NEG | ZRO) ? d->pos : d->pos + l - f->size - a,
		f->sign == -1 ? "-" : sign, a);
	p = f->flag & NEG ? d->pos + a : d->pos + l - f->size;
	ft_memcpy(p, f->buff, f->size);
	d->pos += l;
}

inline void				output(t_field *f, t_data *d)
{
	static char		types[] = {DECIMAL, CHAR, STRING, POINTER, FLOAT};
	static void		(*funcs[])(t_field *, t_data *) = {get_decimal, get_char,
		p_get_string, get_pointer, get_float};
	int				i;

	i = 0;
	while (i < 5)
		if (f->bools & types[i])
		{
			funcs[i](f, d);
			return ;
		}
		else
			i++;
	f->buff = ft_memalloc(1);
	f->size = !!f->inv;
	f->buff[0] = f->inv;
	format(f, d);
	free(f->buff);
}
