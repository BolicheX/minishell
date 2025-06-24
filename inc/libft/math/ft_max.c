/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:52:45 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 16:06:57 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max_i(int *arr, int size)
{
	int	max_i;
	int	i;

	i = 1;
	max_i = 0;
	while (i < size)
	{
		if (arr[i] > arr[max_i])
			max_i = i;
		i++;
	}
	return (max_i);
}

int	ft_max_2(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
