/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:10:39 by jose-jim          #+#    #+#             */
/*   Updated: 2024/11/21 17:02:18 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthex(unsigned int number, int conv)
{
	int	count;

	count = 0;
	if (number >= 16)
	{
		count += ft_puthex((number / 16), conv);
		count += ft_puthex((number % 16), conv);
	}
	else
	{
		if (conv == 'x')
			count = ft_putchar(HEX_LOWCASE[number]);
		else
			count = ft_putchar(HEX_UPCASE[number]);
	}
	return (count);
}
