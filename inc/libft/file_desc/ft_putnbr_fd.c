/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:07:24 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 16:06:09 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
