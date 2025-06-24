/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:19:24 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 16:07:47 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (n <= dstlen)
		return (srclen + n);
	i = dstlen;
	while (*src != '\0' && i < (n - 1))
		*(dst + i++) = *src++;
	*(dst + i) = '\0';
	return (dstlen + srclen);
}

/*
size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((src == NULL || dst == NULL) && n < 1)
		return (0);
	if (n > 0)
	{
		while (dst[i] && i < n)
			i++;
		while (src[j] && j < (n - i - 1) && i < n)
		{
			dst[i + j] = src[j];
			j++;
		}
	}
	dst[i + j] = 0;
	if (i >= n)
		i = n;
	return (i + j);
}
*/
