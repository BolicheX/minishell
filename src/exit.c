/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:43:56 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/23 17:20:57 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_exit_clean(int exit_code, t_ms *ms)
{
	ft_clean_all(ms);
	exit(exit_code);
}

void    ft_exit_perror(char *perror_prefix, int exit_code, t_ms *ms)
{
    if (perror_prefix != NULL)
		perror(perror_prefix);
	else
		perror("Error");
	ft_exit_clean(exit_code, ms);
}

void	ft_exit_error(char *message, int exit_code, t_ms *ms)
{
	if (message != NULL)
		ft_putendl_fd(message, STDERR_FILENO);
	ft_exit_clean(exit_code, ms);
}
