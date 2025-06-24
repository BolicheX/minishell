/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countlines_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:49:32 by jose-jim          #+#    #+#             */
/*   Updated: 2025/06/24 16:05:59 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countlines_fd(int fd)
{
	int		bytes;
	int		lines;
	int		i;
	char	buff[BUFFER_SIZE];
	char	last;

	bytes = 1;
	lines = 0;
	while (bytes > 0)
	{
		i = 0;
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
			return (-1);
		while (i < bytes)
		{
			if (buff[i] == '\n')
				lines++;
			last = buff[i];
			i++;
		}
	}
	return (lines + (last != '\n'));
}
