/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 05:22:36 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 17:48:58 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include "../../libft.h"
# include "parse.h"
# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_data
{
	char		*buff;
	char		*pos;
	size_t		size;
	size_t		g_null;
	va_list		args;
}				t_data;

typedef union	u_wchar
{
	unsigned int	n;
	char			c[4];
}				t_wchar;

# define B		__attribute__ ((format (printf, 1, 2)))
# define A		int	ft_printf(const char *format, ...) B;

A;
# undef A
# undef B

void			*p_try(size_t size);
void			p_die(char *buff, int exit_code);
int				ft_vaprintf(const char *format, va_list args);
void			p_realloc(t_data *d);
void			fast_copy(void *src, void *dest, size_t size);
char			*param(char *s, t_data *d);
char			*string(char *s, t_data *d);
void			output(t_field *f, t_data *d);
void			get_decimal(t_field *f, t_data *d);
void			p_get_string(t_field *f, t_data *d);
void			get_char(t_field *f, t_data *d);
void			get_pointer(t_field *f, t_data *d);
void			get_float(t_field *f, t_data *d);
uint64_t		cast_uchar(uint64_t n, int *sign);
uint64_t		cast_char(uint64_t n, int *sign);
uint64_t		cast_ushort(uint64_t n, int *sign);
uint64_t		cast_short(uint64_t n, int *sign);
uint64_t		cast_uint(uint64_t n, int *sign);
uint64_t		cast_int(uint64_t n, int *sign);
uint64_t		cast_uint64(uint64_t n, int *sign);
uint64_t		cast_int64(uint64_t n, int *sign);
void			debug(t_field f, char *string);
void			itoa64base(uint64_t n, int base, t_field *f);
char			*wstr(unsigned int *s, t_field *f);
size_t			get_wchar(unsigned int *n);
void			format(t_field *f, t_data *d);

#endif
