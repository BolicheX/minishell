/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arraylen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:37:06 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/18 14:56:28 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t  ft_str_arraylen(char **array)
{
    size_t  i;

    i = 0;
    while (array[i] != NULL)
        i++;
    return (i);
}
