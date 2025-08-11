/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:51:45 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/08 18:57:00 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnum_space(char *str)
{
    while (ft_isspace(*str))
        str++;
    if (*str == '+' || *str == '-')
        str++;
    if (ft_isdigit(*str) == 0)
        return (0);
    while (ft_isdigit(*str))
        str++;
    while (ft_isspace(*str))
        str++;
    return (*str == '\0');
}
