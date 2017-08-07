/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:12:53 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 17:41:12 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static int	cf(void *f1, void *f2)
{
	return ((FILE(f1)->fd == FILE(f2)->fd));
}

static int	ft_realloc(t_file *file, char *buff, int len)
{
	char	*cpy;
	int		end;

	end = file->offset - file->read;
	if (len + file->offset >= file->size)
	{
		if (len + end >= file->size)
		{
			if ((cpy = ft_memalloc(file->size + BUFFSIZE)) == NULL)
				return (-1);
			file->size += BUFFSIZE;
			ft_memcpy(cpy, file->buff + file->read, end);
			free(file->buff);
			file->buff = cpy;
		}
		else if (end > 0)
			ft_memmove(file->buff, file->buff + file->read, end);
		ft_bzero(file->buff + end, file->size - end);
		file->read = 0;
		file->offset = end > 0 ? end : 0;
	}
	ft_memcpy(file->buff + file->offset, buff, len);
	file->offset += len;
	return (0);
}

static int	g_getline(t_file *file, char **line)
{
	char	*p;
	char	buff[BUFFSIZE + 1];
	int		len;

	ft_bzero(buff, BUFFSIZE);
	if (!file->buff && (file->buff = ft_memalloc(BUFFSIZE + 1)) == NULL)
		return (-1);
	while (1)
	{
		if ((p = ft_strchr(file->buff + file->read, '\n')) != NULL)
		{
			len = p - (file->buff + file->read);
			*line = ft_strndup(file->buff + file->read, len);
			file->read += len + 1;
			return (*line ? 1 : -1);
		}
		if ((len = read(file->fd, buff, BUFFSIZE)) < 0)
			return (-1);
		if (!len)
			return ((*line = ft_strdup(file->buff + file->read)) ? 0 : -1);
		if (ft_realloc(file, buff, len) == -1)
			return (-1);
	}
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	static t_circular	*files = NULL;
	t_circular			*node;
	t_file				*file;
	t_file				temp;
	int					ret;

	temp = (t_file){fd, 0, 0, BUFFSIZE + 1, 0};
	node = ft_circular_find(files, &temp, cf);
	if ((file = node ? (t_file *)node->content : (t_file *)
		ft_circular_add_head(&files, ft_circular_new((void *)&temp,
		sizeof(t_file)))->content) == NULL)
		return (-1);
	ret = g_getline(file, line);
	if (!ret)
	{
		ft_memdel((void **)&file->buff);
		ft_circular_delete_node(&files, ft_circular_find(files, file, cf));
	}
	return (ret);
}
