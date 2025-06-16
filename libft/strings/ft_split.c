/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:47:48 by jose-jim          #+#    #+#             */
/*   Updated: 2024/10/31 12:42:12 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	next_delimiter(char const *str, char c, int i)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	next_word(char const *str, char c, int i)
{
	while (str[i] && str[i] == c)
		i++;
	return (i);
}

static int	count_words(const char *str, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			words++;
			i = next_delimiter(str, c, i);
		}
		else
			i++;
	}
	return (words);
}

static void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	**ft_split(const char *str, char c)
{
	char	**res;
	int		wrds;
	int		i;
	int		j;

	wrds = count_words(str, c);
	res = (char **) malloc(sizeof(char *) * (wrds + 1));
	if (!str || !res)
		return (NULL);
	i = 0;
	j = 0;
	while (j < wrds)
	{
		i = next_word(str, c, i);
		res[j] = ft_substr(str, i, next_delimiter(str, c, i) - i);
		if (!res[j])
		{
			free_split(res);
			return (NULL);
		}
		i = next_delimiter(str, c, i);
		j++;
	}
	res[j] = NULL;
	return (res);
}
