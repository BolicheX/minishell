/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:10:39 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 16:05:15 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
