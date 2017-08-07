/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 00:42:45 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/25 00:43:03 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "defines.h"

typedef struct	s_field
{
	int				prec;
	int				padd;
	int				mods;
	int				spec;
	int				sign;
	char			flag;
	char			inv;
	unsigned char	bools;
	char			*buff;
	size_t			size;
}				t_field;

int				conv(char *s, t_field *f);
void			reduce(t_field *f);

#endif
