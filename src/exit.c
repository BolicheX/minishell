/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:43:56 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/17 16:42:46 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *perror_prefix)
{
	if (perror_prefix != NULL)
	{
		ft_putstr_fd("-minishell: ", STDERR_FILENO);
		perror(perror_prefix);
	}
	else
		perror("-minishell: error");
}

void    ft_exit_perror(char *perror_prefix, int exit_code, t_ms *ms)
{
    ft_perror(perror_prefix);
	ft_exit_clean(exit_code, ms);
}

void	ft_error(const char *context, const char *msg, int exit_code)
{
	if (context && msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd((char *)context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd((char *)msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else if (context)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(context);
	}
	else
		perror("minishell");
	(void)exit_code;
}

void	ft_exit_error(char *msg, int exit_code, t_ms *ms)
{
	ft_error(msg, NULL, exit_code);
	ft_exit_clean(exit_code, ms);
}

void    ft_exit_clean(int exit_code, t_ms *ms)
{
	ft_clean_all(ms);
	exit(exit_code);
}
