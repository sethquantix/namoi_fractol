/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 05:15:52 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 05:25:14 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	p_realloc(t_data *d)
{
	char	*t;
	size_t	pos;

	pos = d->pos - d->buff;
	if ((t = ft_memalloc(d->size + BUFFSIZE)) == NULL)
		p_die(d->buff, EXIT_FAILURE);
	if (d->buff)
		ft_memcpy(d->buff, t, d->size);
	d->size += BUFFSIZE;
	ft_memdel((void **)&d->buff);
	d->buff = t;
	d->pos = d->buff + pos;
}

int		ft_vasprintf(char **buff, const char *format, va_list args)
{
	static char	*(*f[3])(char *, t_data *) = {param, string};
	t_data		d;
	size_t		wr;
	char		*s;

	s = (char *)format;
	ft_bzero(&d, sizeof(t_data));
	va_copy(d.args, args);
	p_realloc(&d);
	while (*s)
	{
		if (*s == '%')
			s = f[0](s, &d);
		else
			s = f[1](s, &d);
	}
	va_end(d.args);
	wr = d.pos - d.buff;
	*buff = ft_strndup(d.buff, wr);
	ft_memdel((void **)&d.buff);
	return (wr + d.g_null);
}

int		ft_sprintf(char **buff, const char *format, ...)
{
	va_list		args;
	int			ret;

	va_start(args, format);
	ret = ft_vasprintf(buff, format, args);
	va_end(args);
	return (ret);
}

int		ft_vaprintf(const char *format, va_list args)
{
	static char	*(*f[3])(char *, t_data *) = {param, string};
	t_data		d;
	size_t		wr;
	char		*s;

	s = (char *)format;
	ft_bzero(&d, sizeof(t_data));
	va_copy(d.args, args);
	p_realloc(&d);
	while (*s)
	{
		if (*s == '%')
			s = f[0](s, &d);
		else
			s = f[1](s, &d);
	}
	va_end(d.args);
	wr = d.pos - d.buff;
	write(1, d.buff, wr);
	ft_memdel((void **)&d.buff);
	return (wr + d.g_null);
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			ret;

	va_start(args, format);
	ret = ft_vaprintf(format, args);
	va_end(args);
	return (ret);
}
