/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circular_find.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:41:09 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/20 12:43:49 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_circular	*ft_circular_find(t_circular *head, void *data,
	int (*f)(void *, void *))
{
	t_circular	*node;

	node = head;
	if (!node)
		return (NULL);
	while (node->next != head)
		if (f(node->content, data))
			return (node);
		else
			node = node->next;
	return (f(node->content, data) ? node : NULL);
}
