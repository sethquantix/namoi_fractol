/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circular_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:14:36 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/20 12:35:33 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_circular	*ft_circular_new(void *content, size_t size)
{
	t_circular	*node;

	if ((node = ft_memalloc(sizeof(t_circular))) == NULL)
		return (NULL);
	node->prev = node;
	node->next = node;
	if (size && (node->content = ft_memalloc(size)) == NULL)
	{
		free(node);
		return (NULL);
	}
	if (node->content)
		ft_memcpy(node->content, content, size);
	node->size = size;
	return (node);
}

t_circular	*ft_circular_add_tail(t_circular **head, t_circular *node)
{
	if (!*head)
		return (*head = node);
	node->next = *head;
	node->prev = (*head)->prev;
	(*head)->prev->next = node;
	(*head)->prev = node;
	return (node);
}

t_circular	*ft_circular_add_head(t_circular **head, t_circular *node)
{
	return (*head = ft_circular_add_tail(head, node));
}

void		ft_circular_delete_node(t_circular **head, t_circular *old)
{
	t_circular *node;

	node = *head;
	if (!node)
		return ;
	if (old == node)
	{
		ft_memdel((void **)&node->content);
		ft_memdel((void **)head);
		return ;
	}
	while (node->next != *head)
		if (node == old)
		{
			node->next->prev = node->prev;
			node->prev->next = node->next;
			ft_memdel((void **)&node->content);
			ft_memdel((void **)&node);
			return ;
		}
		else
			node = node->next;
}

void		ft_circular_free(t_circular **head)
{
	t_circular *node;

	if (!*head)
		return ;
	if ((*head)->prev)
		(*head)->prev->next = NULL;
	node = *head;
	*head = node->next;
	(*head)->prev = NULL;
	ft_memdel((void **)&node->content);
	ft_memdel((void **)&node);
	ft_circular_free(head);
}
