/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:13:02 by jose-jim          #+#    #+#             */
/*   Updated: 2024/10/31 12:41:57 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_b;
	unsigned const char	*src_b;

	i = 0;
	dst_b = (unsigned char *)dst;
	src_b = (unsigned const char *)src;
	if ((dst_b == NULL && src_b == NULL) || dst_b == src_b)
		return (dst);
	if (src_b < dst_b)
	{
		while (n--)
			*(dst_b + n) = *(src_b + n);
	}
	else
	{
		while (i < n)
		{
			*(dst_b + i) = *(src_b + i);
			i++;
		}
	}
	return (dst);
}

/*
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int		main(void)
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	*dest;
	int		arg;

	dest = src + 1;
	if (src != ft_memmove(src, dest, 8))
		write(1, "dest's adress was not returned\n", 31);
	write(1, dest, 22);
	return (0);
}*/
