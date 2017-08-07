/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 00:43:18 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/25 00:43:29 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static inline int	set(void *p, int v, size_t size, int ret)
{
	int		i;

	if (size == sizeof(int))
		ft_memcpy(p, &v, size);
	else
		*(char *)p |= 1 << (char)v;
	if (ret > 0)
		return (ret);
	i = 1;
	while (v / 10)
	{
		i++;
		v /= 10;
	}
	return (i - ret);
}

inline int			conv(char *s, t_field *f)
{
	static char	*m[] = MODS;
	static char *v[2] = {CONV, FLAG};
	char		*t;
	int			i;

	if ((t = ft_strchr(v[0], *s)) != NULL)
		return (set(&f->spec, (int)(t - v[0]), sizeof(int), 1));
	if ((t = ft_strchr(v[1], *s)) != NULL)
		return (set(&f->flag, (int)(t - v[1]), sizeof(char), 1));
	i = -1;
	while (m[++i])
	{
		if (ft_strncmp(m[i], s, ft_strlen(m[i])) == 0)
			return (i >= f->mods ? set(&f->mods, i, sizeof(int),
			ft_strlen(m[i])) : ft_strlen(m[i]));
	}
	if (*s == '.')
		return (ft_isdigit(*(s + 1)) ? set(&f->prec, ft_atoi(s + 1),
		sizeof(int), -1) : set(&f->prec, 0, sizeof(int), 1));
	else if (ft_isdigit(*s))
		return (set(&f->padd, ft_atoi(s), sizeof(int), 0));
	f->inv = *s;
	return (set(&f->spec, -1, sizeof(int), 1));
}

inline void			reduce(t_field *f)
{
	f->bools = (f->spec == LCS || f->spec == UCS) << 0;
	f->bools |= (f->spec == LFS || f->spec == UFS) << 1;
	f->bools |= (f->spec == LXS || f->spec == UXS) << 2;
	f->bools |= (f->spec == LOS || f->spec == UOS) << 3;
	f->bools |= (f->spec == LUS || f->spec == UUS) << 4;
	f->bools |= (f->spec == LSS || f->spec == USS) << 5;
	f->bools |= (f->spec == LDS || f->spec == UDS) << 6;
	f->bools |= (f->spec == LPS) << 7;
	CHECK(f->flag, (f->bools & DECIMAL) && (f->prec != -1), 0xFF ^ ZRO);
	CHECK(f->flag, f->bools & 0x0, 0xFF ^ ZRO);
	CHECK(f->flag, f->bools & 0x71, 0xFF ^ ALT);
	CHECK(f->flag, f->flag & NEG, 0xFF ^ ZRO);
	CHECK(f->flag, (f->flag & PLS) | (f->bools & US), 0xFF ^ SPC);
	CHECK(f->flag, !(f->bools & 0x52), 0xFF ^ THD);
	CHECK(f->mods, !(f->bools & FLOAT) && f->mods == CLM, 0);
	CHECK(f->mods, (f->bools & FLOAT) && f->mods != CLM, 0);
	CHECK(f->mods, (f->bools & TEXT) && f->mods != L_M, 0);
	if (f->spec == UDS || f->spec == UCS || f->spec == USS || f->spec == UUS)
	{
		f->spec--;
		f->mods = f->mods < L_M ? L_M : f->mods;
	}
	if (f->spec == LPS)
		f->flag |= ALT;
}
