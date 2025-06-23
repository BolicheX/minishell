/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:01:10 by jescuder          #+#    #+#             */
/*   Updated: 2022/10/01 23:37:36 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void	*))
{
	t_list	*p;
	t_list	*aux;

	if (!lst || !del)
		return ;
	p = *lst;
	while (p)
	{
		aux = p->next;
		ft_lstdelone(p, del);
		p = aux;
	}
	*lst = 0;
}
