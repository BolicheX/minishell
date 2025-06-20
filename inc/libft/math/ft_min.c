/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:28:58 by jose-jim          #+#    #+#             */
/*   Updated: 2025/04/24 18:04:21 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_min_i(int *arr, int size)
{
	int	min_i;
	int	i;

	min_i = 0;
	i = 1;
	while (i < size)
	{
		if (arr[i] < arr[min_i])
			min_i = i;
		i++;
	}
	return (min_i);
}
