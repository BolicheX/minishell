/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:34:14 by jose-jim          #+#    #+#             */
/*   Updated: 2024/10/31 12:41:47 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
