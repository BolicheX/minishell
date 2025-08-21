/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:10:29 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 23:28:25 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_str_array(char **array)
{
	size_t	i;

	if (array == NULL)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
	return (NULL);
}
