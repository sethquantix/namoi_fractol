/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 18:15:15 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 04:12:10 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char			*d;
	char			*s;
	unsigned long	*ld;
	unsigned long	*ls;

	if (n == 0 || !dst || !src)
		return (dst);
	ld = (unsigned long *)dst;
	ls = (unsigned long *)src;
	while (n >= 8)
	{
		*(ld++) = *(ls++);
		n -= 8;
	}
	d = (char *)ld;
	s = (char *)ls;
	if (n == 0)
		return (dst);
	while (n--)
		*(d++) = *(s++);
	return (dst);
}
