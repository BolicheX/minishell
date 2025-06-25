/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:02:19 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/25 14:54:17 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_kvl_clear(t_kvl **lst, void (*del)(void    *))
{
	t_kvl    *node;
	t_kvl    *next;

	if (lst == NULL || del == NULL)
		return ;
	node = *lst;
	while (node != NULL)
	{
		next = node->next;
        ft_kvl_delone(node, del);
		node = next;
	}
	*lst = NULL;
}
