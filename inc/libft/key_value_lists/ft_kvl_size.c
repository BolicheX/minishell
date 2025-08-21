/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:36:08 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 23:15:50 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_kvl_size(t_kvl *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
