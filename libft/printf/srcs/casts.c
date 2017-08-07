/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 11:39:42 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 03:33:23 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

uint64_t	cast_uchar(uint64_t n, int *sign)
{
	unsigned char	ret;

	ret = (unsigned char)n;
	*sign = 1;
	return ((uint64_t)ret);
}

uint64_t	cast_char(uint64_t n, int *sign)
{
	char	ret;

	ret = (char)n;
	*sign = ret < 0 ? -1 : 1;
	return (*sign == -1 ? (uint64_t)(-(ret + 1)) + 1 : (uint64_t)ret);
}

uint64_t	cast_ushort(uint64_t n, int *sign)
{
	unsigned short	ret;

	ret = (unsigned short)n;
	*sign = 1;
	return ((uint64_t)ret);
}

uint64_t	cast_short(uint64_t n, int *sign)
{
	short	ret;

	ret = (short)n;
	*sign = ret < 0 ? -1 : 1;
	return (*sign == -1 ? (uint64_t)(-(ret + 1)) + 1 : (uint64_t)ret);
}

uint64_t	cast_int(uint64_t n, int *sign)
{
	int	ret;

	ret = (int)n;
	*sign = ret < 0 ? -1 : 1;
	return (*sign == -1 ? (uint64_t)(-(ret + 1)) + 1 : (uint64_t)ret);
}
