/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/23 03:23:33 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 03:36:16 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	p_die(char *buff, int exit_code)
{
	ft_memdel((void **)&buff);
	exit(exit_code);
}

void	*p_try(size_t size)
{
	void	*p;

	if ((p = ft_memalloc(size)) == NULL)
		exit(EXIT_FAILURE);
	return (p);
}
