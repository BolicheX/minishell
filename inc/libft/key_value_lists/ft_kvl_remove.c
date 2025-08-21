/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:57:40 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 23:20:58 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_kvl_remove(t_kvl **lst, char *key, void (*del)(void *))
{
	t_kvl	*previous;
	t_kvl	*node;

	node = *lst;
	while (node != NULL)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			if (node == *lst)
				*lst = node->next;
			else
				previous->next = node->next;
			ft_kvl_delone(node, del);
			return (1);
		}
		previous = node;
		node = node->next;
	}
	return (0);
}
