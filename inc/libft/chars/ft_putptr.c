/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:08:22 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 16:05:23 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(unsigned long n)
{
	char		*hex;
	static int	i;

	i = 0;
	hex = "0123456789abcdef";
	if (n == 0)
	{
		ft_printf("%s", "(nil)");
		return (5);
	}
	if (n >= 16)
		ft_putptr(n / 16);
	if (i == 0)
		i += write(1, "0x", 2);
	i += write (1, &hex[n % 16], 1);
	return (i);
}
