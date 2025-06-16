/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:12:17 by jose-jim          #+#    #+#             */
/*   Updated: 2025/04/22 17:29:51 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_mean(int *n, int size)
{
	int	i;
	int	mean;

	if (size == 0)
		return (0);
	mean = 0;
	i = -1;
	while (++i < size)
		mean = mean + n[i];
	return (mean / size);
}
