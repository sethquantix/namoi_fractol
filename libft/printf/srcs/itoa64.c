/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 06:48:07 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 03:34:49 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	itoa64base(uint64_t n, int base, t_field *f)
{
	static char		chars[] = "0123456789abcdef";
	size_t			size;
	uint64_t		t;
	int				i;

	t = n;
	size = 0;
	while (t)
	{
		size++;
		t /= base;
	}
	size = !n && f->prec ? 1 : size;
	size = MAX(size, (size_t)((f->prec != -1) * f->prec));
	if (!(f->size = size))
		return ;
	f->buff = p_try(size + 1);
	ft_memset(f->buff, '0', size);
	i = size - 1;
	while (i >= 0 && f->buff[i] == '0')
	{
		f->buff[i--] = (f->spec == UXS) ? ft_toupper(chars[n % base]) :
			chars[n % base];
		n /= base;
	}
}
