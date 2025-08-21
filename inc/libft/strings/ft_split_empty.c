/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:14:45 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 23:27:40 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_len(const char *str, char c)
{
	size_t	len;
	size_t	i;

	len = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			len++;
		i++;
	}
	return (len);
}

static char	**ft_fill_array(const char *str, char c, char **array)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			array[j] = ft_substr(str, start, i - start);
			if (array[j] == NULL)
				return (ft_free_str_array(array));
			j++;
			start = i + 1;
		}
		i++;
	}
	array[j] = ft_substr(str, start, i - start);
	return (array);
}

char	**ft_split_empty(const char *str, char c)
{
	char	**array;
	size_t	len;

	len = ft_get_len(str, c);
	array = malloc(sizeof(char *) * (len + 1));
	if (array == NULL)
		return (NULL);
	array[len] = NULL;
	return (ft_fill_array(str, c, array));
}
