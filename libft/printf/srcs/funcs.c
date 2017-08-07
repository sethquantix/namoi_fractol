/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 06:10:05 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 03:32:48 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

char			*string(char *s, t_data *d)
{
	int		k;

	k = 0;
	while (s[k] != '%' && s[k])
		k++;
	if (d->pos + (size_t)k > d->size + d->buff)
		p_realloc(d);
	ft_memcpy(d->pos, s, k);
	d->pos += k;
	return (s + k);
}

inline char		*param(char *s, t_data *d)
{
	t_field		f;
	char		*p;

	p = s;
	ft_bzero(&f, sizeof(t_field));
	f.prec = -1;
	s++;
	while (*s && !f.spec)
		s += conv(s, &f);
	reduce(&f);
	output(&f, d);
	return (s);
}
