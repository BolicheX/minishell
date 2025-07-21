/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:02:19 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/20 20:44:29 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_kvl *ft_kvl_clear(t_kvl **lst, void (*del)(void *))
{
	t_kvl	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_kvl_delone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
	return (NULL);
}
