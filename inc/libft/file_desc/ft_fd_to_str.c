/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:04:13 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/18 19:42:52 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int  ft_init(char **accumulator, char **buffer)
{
    *accumulator = malloc(sizeof(char) * 1);
    if (*accumulator == NULL)
        return (0);
    (*accumulator)[0] = '\0';
    *buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (*buffer == NULL)
    {
        free(*accumulator);
        return (0);
    }
    return (1);
}

char    *ft_fd_to_str(int fd)
{
    char    *accumulator;
    char    *buffer;
    ssize_t bytes_read;

    if (ft_init(&accumulator, &buffer) == 0)
        return (NULL);
    bytes_read = read(fd, buffer, BUFFER_SIZE);
    while (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';
        accumulator = ft_strjoin_free(accumulator, buffer);
        if (accumulator == NULL)
        {
            free(buffer);
            return (NULL);
        }
        bytes_read = read(fd, buffer, BUFFER_SIZE);
    }
    free(buffer);
    if (bytes_read == -1)
    {
        free(accumulator);
        return (NULL);
    }
    return (accumulator);
}
