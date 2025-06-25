/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:37:51 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/25 14:54:17 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_kvl_get(t_kvl *lst, char *key)
{
	while (lst != NULL)
	{
        if (ft_strcmp(lst->key, key) == 0)
            return (lst->value);
		lst = lst->next;
	}
    return (NULL);
}
