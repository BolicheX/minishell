/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:02:19 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 23:16:01 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_kvl	*ft_kvl_clear(t_kvl **lst, void (*del)(void *))
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
