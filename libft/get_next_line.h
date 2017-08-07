/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:46:16 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/20 12:55:14 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFSIZE	256
# define FILE(x)	((t_file *)x)
# include <fcntl.h>

typedef struct	s_file
{
	int		fd;
	int		read;
	int		offset;
	int		size;
	char	*buff;
}				t_file;

#endif
