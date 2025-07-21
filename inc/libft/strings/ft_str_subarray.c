/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_subarray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:27:45 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/18 14:56:33 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    **ft_str_subarray(char **array, size_t start, size_t len)
{
    size_t  array_len;
    char    **subarray;
    size_t  i;

    if (array == NULL)
        return (NULL);
    array_len = ft_str_arraylen(array);
    if (start > array_len)
        len = 0;
    else if (len > array_len - start)
        len = array_len - start;
    subarray = malloc(sizeof(char *) * (len + 1));
    if (subarray == NULL)
        return (NULL);
    i = 0;
    while (i < len && array[start] != NULL)
    {
        subarray[i] = ft_strdup(array[start]);
        if (subarray[i] == NULL)
            return (ft_free_str_array(subarray));
        i++;
        start++;
    }
    subarray[i] = NULL;
    return (subarray);
}
