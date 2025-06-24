/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:57:29 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/24 20:00:10 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_open_read(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        ft_perror(filename);
    return (fd);
}

//The second argument determines either truncating(>) or appending(>>).
int ft_open_write(char *filename, int is_truncating)
{
    int flags;
    int fd;

    flags = O_WRONLY | O_CREAT;
    if (is_truncating == 1)
        flags |= O_TRUNC;
    fd = open(filename, flags, 0644);
    if (fd == -1)
        ft_perror(filename);
    return (fd);
}
