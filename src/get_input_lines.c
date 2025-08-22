/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:14:30 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/22 12:24:33 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_get_len(const char *input)
{
	size_t	len;
	size_t	i;
	int		simple;
	int		doubl;

	simple = 0;
	doubl = 0;
	len = 1;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' && doubl == 0)
			simple = !simple;
		else if (input[i] == '\"' && simple == 0)
			doubl = !doubl;
		else if (input[i] == '\n' && simple == 0 && doubl == 0)
			len++;
		i++;
	}
	return (len);
}

static char	**ft_fill_array(char *input, char **array, int simple, int doubl)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' && doubl == 0)
			simple = !simple;
		else if (input[i] == '\"' && simple == 0)
			doubl = !doubl;
		else if (input[i] == '\n' && simple == 0 && doubl == 0)
		{
			array[j] = ft_substr(input, start, i - start);
			if (array[j] == NULL)
				return (ft_free_str_array(array));
			j++;
			start = i + 1;
		}
		i++;
	}
	array[j] = ft_substr(input, start, i - start);
	return (array);
}

char	**ft_get_input_lines(char *input)
{
	char	**input_lines;
	size_t	len;

	len = ft_get_len(input);
	input_lines = malloc(sizeof(char *) * (len + 1));
	if (input_lines == NULL)
		return (NULL);
	input_lines[len] = NULL;
	return (ft_fill_array(input, input_lines, 0, 0));
}
