/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:09:49 by jose-jim          #+#    #+#             */
/*   Updated: 2024/11/21 17:02:12 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		count += ft_putchar('-');
		count += ft_putchar('2');
		count += ft_putnbr(147483648);
	}
	else if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
		count += ft_putnbr(nb);
	}
	else if (nb > 9)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putnbr(nb % 10);
	}
	else
		count += ft_putchar(nb + 48);
	return (count);
}

int	ft_putnbr_unsign(unsigned int n)
{
	unsigned int	nbr;

	nbr = 0;
	if (n <= 9)
		return (ft_putchar((n + 48)));
	else
	{
		nbr += ft_putnbr_unsign(n / 10);
		nbr += ft_putchar((n % 10) + 48);
	}
	return (nbr);
}
