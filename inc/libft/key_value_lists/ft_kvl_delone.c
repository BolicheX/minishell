/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_delone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:58:18 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 23:21:17 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_kvl_delone(t_kvl *node, void (*del)(void *))
{
	if (node == NULL || del == NULL)
		return ;
	free(node->key);
	del(node->value);
	free(node);
}
