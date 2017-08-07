/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 17:14:39 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/25 12:43:00 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, char c, size_t len)
{
	unsigned char	*p;

	if (!len)
		return (s);
	p = (unsigned char *)s;
	while (len--)
		*(p++) = c;
	return (s);
}
