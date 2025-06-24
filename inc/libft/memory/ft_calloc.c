/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:34:14 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 16:07:12 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	ptr = (void *)malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		*(char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}
