/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:28:58 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 16:07:03 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
