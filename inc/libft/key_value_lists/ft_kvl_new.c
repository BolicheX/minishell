/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:16:11 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/20 21:22:31 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_kvl    *ft_kvl_new(char *key, void *value)
{
	t_kvl    *new;

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

