/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:00:12 by jose-jim          #+#    #+#             */
/*   Updated: 2025/01/20 01:18:49 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_free1(char *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	free(s1);
	s1 = 0;
	return (str);
}

char	*add_buff(int fd, char *save, char *buff)
{
	int		bytes;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes < 0)
		{
			free(save);
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		if (!save)
			save = (char *)ft_calloc(sizeof(char), 1);
		save = ft_strjoin_free1(save, buff);
		if (ft_strchr(save, '\n'))
			break ;
	}
	return (save);
}

char	*cut_line(char **save)
{
	size_t	cut;
	char	*line;
	char	*tmp;

	cut = 0;
	while ((*save)[cut] && (*save)[cut] != '\n')
		cut++;
	line = ft_substr(*save, 0, cut + 1);
	tmp = *save;
	*save = ft_substr(tmp, cut + 1, ft_strlen(*save) - cut);
	free(tmp);
	if (**save == '\0')
	{
		free(*save);
		*save = 0;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	save = add_buff(fd, save, buff);
	free(buff);
	buff = 0;
	if (!save)
		return (NULL);
	line = cut_line(&save);
	if (!line)
		return (NULL);
	return (line);
}
