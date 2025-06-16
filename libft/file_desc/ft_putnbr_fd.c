/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:07:24 by jose-jim          #+#    #+#             */
/*   Updated: 2024/10/31 12:41:35 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	char		nb_c;

	nb = (long int)n;
	if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		nb = nb % 10;
	}
	if (nb < 10)
	{
		nb_c = nb + '0';
		write(fd, &nb_c, 1);
	}
}
