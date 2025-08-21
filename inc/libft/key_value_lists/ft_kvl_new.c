/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:16:11 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 23:21:39 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_kvl	*ft_kvl_new(char *key, void *value)
{
	t_kvl	*new;

	new = malloc(sizeof(t_kvl));
	if (new == NULL)
		return (NULL);
	new->key = ft_strdup(key);
	if (new->key == NULL)
	{
		free(new);
		return (NULL);
	}
	new->value = value;
	new->next = NULL;
	return (new);
}
