/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casts2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 12:05:51 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/26 12:06:22 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

uint64_t	cast_uint(uint64_t n, int *sign)
{
	unsigned int	ret;

	ret = (unsigned int)n;
	*sign = 1;
	return ((uint64_t)ret);
}

uint64_t	cast_uint64(uint64_t n, int *sign)
{
	*sign = 1;
	return (n);
}

uint64_t	cast_int64(uint64_t n, int *sign)
{
	int64_t	ret;

	ret = (int64_t)n;
	*sign = ret < 0 ? -1 : 1;
	return (*sign == -1 ? (uint64_t)(-(ret + 1)) + 1 : (uint64_t)ret);
}
