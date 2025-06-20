/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:52:45 by jose-jim          #+#    #+#             */
/*   Updated: 2025/04/22 17:29:54 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
