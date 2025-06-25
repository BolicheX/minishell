/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:20:15 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/25 19:10:09 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Updates the node with this key or creates a new one if it doesn't exist.
//Returns the old value if the node existed or the new value if not.
void    *ft_kvl_set(t_kvl **lst, char *key, void *value)
{
	t_kvl    *node;
	t_kvl    *new;
	void    *old_value;

	node = *lst;
	while (node != NULL)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			old_value = node->value;
			node->value = value;
			return (old_value);
		}
		node = node->next;
	}
	new = ft_kvl_new(key, value);
	if (new == NULL)
		return (NULL);
	ft_kvl_add(lst, new);
	return (value);
}
