/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 09:43:42 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/25 09:43:44 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static inline unsigned int	reverse(unsigned int n, int j, unsigned int t)
{
	t_wchar	w;

	w.n = n;
	while (j--)
	{
		w.c[j] = t & 0xff;
		t >>= 8;
	}
	return (w.n);
}

inline size_t				get_wchar(unsigned int *n)
{
	t_wchar			wc;
	unsigned int	t;
	size_t			i;
	size_t			j;

	t = *n;
	wc.n = (t > BYTE2) ? MASK_2 : 0;
	wc.n = (t > BYTE3) ? MASK_3 : wc.n;
	wc.n = (t > BYTE4) ? MASK_4 : wc.n;
	i = ((t > BYTE4) ? 1 : 0) + ((t > BYTE3) ? 1 : 0) + ((t > BYTE2) ? 1 : 0);
	j = i;
	while (j)
	{
		wc.n |= (t & 0x3F) << ((i - j) * 8);
		t >>= 6;
		j--;
	}
	wc.n |= t << (8 * (i));
	t = wc.n;
	*n = reverse(wc.n, i + 1, t);
	return (i + 1);
}

inline char					*wstr(unsigned int *s, t_field *f)
{
	size_t			len;
	unsigned int	*t;
	char			*buff;
	char			*p;
	t_wchar			w;

	t = s;
	len = 0;
	while (*(t++))
		++len;
	buff = ft_memalloc(sizeof(int) * len);
	p = buff;
	while (*s)
	{
		w.n = *s;
		len = get_wchar(&w.n);
		if (p + len - buff > f->prec && f->prec != -1)
			break ;
		ft_memcpy(p, w.c, len);
		p += len;
		s++;
	}
	f->size = p - buff;
	return (buff);
}
