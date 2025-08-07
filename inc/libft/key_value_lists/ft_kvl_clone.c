/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kvl_clone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:53:03 by jose-jim          #+#    #+#             */
/*   Updated: 2025/08/07 22:53:21 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_kvl	*ft_kvl_strclone(t_kvl *env)
{
	t_kvl	*clone;
	t_kvl	*node;
	char	*value_dup;

	clone = NULL;
	while (env)
	{
		value_dup = NULL;
		if (env->value)
		{
			value_dup = ft_strdup(env->value);
			if (!value_dup)
				return (ft_kvl_clear(&clone, free));
		}
		node = ft_kvl_new(env->key, value_dup);
		if (!node)
		{
			free(value_dup);
			return (ft_kvl_clear(&clone, free));
		}
		ft_kvl_add(&clone, node);
		env = env->next;
	}
	return (clone);
}
