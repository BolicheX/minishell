/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:50:06 by jescuder          #+#    #+#             */
/*   Updated: 2022/10/02 17:52:41 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*create_elements(t_list *lst, t_list *p, \
	void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*last;

	result = p;
	while (lst)
	{
		last = p;
		p = ft_lstnew(f(lst->content));
		if (!p)
		{
			ft_lstclear(&result, del);
			return (0);
		}
		last->next = p;
		lst = lst->next;
	}
	return (result);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;

	if (!lst || !f)
		return (0);
	p = ft_lstnew(f(lst->content));
	if (!p)
	{
		ft_lstclear(&p, del);
		return (0);
	}
	lst = lst->next;
	return (create_elements(lst, p, f, del));
}
