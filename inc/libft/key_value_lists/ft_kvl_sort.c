/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:50:19 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/07 22:50:47 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_kvl	*ft_kvl_alphasort(t_kvl *lst)
{
	t_kvl	*sorted;
	t_kvl	*curr;
	t_kvl	*pos;

	sorted = NULL;
	while (lst)
	{
		curr = lst;
		lst = lst->next;
		if (!sorted || ft_strcmp(curr->key, sorted->key) < 0)
		{
			curr->next = sorted;
			sorted = curr;
		}
		else
		{
			pos = sorted;
			while (pos->next && ft_strcmp(curr->key, pos->next->key) > 0)
				pos = pos->next;
			curr->next = pos->next;
			pos->next = curr;
		}
	}
	return (sorted);
}
