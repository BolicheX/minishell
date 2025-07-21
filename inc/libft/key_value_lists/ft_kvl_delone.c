/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_delone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:18 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/20 20:44:35 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_kvl_delone(t_kvl *node, void (*del)(void    *))
{
	if (node == NULL || del == NULL)
		return ;
	free(node->key);
	del(node->value);
	free(node);
}
