/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:43:56 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/11 21:25:56 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *perror_prefix)
{
	if (perror_prefix != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(perror_prefix);
	}
	else
		perror("minishell: error");
}

void    ft_exit_perror(char *perror_prefix, int exit_code, t_ms *ms)
{
    ft_perror(perror_prefix);
	ft_exit_clean(exit_code, ms);
}

int	ft_error(char *cmd, char *arg, char *msg, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
/* 	else
		ft_putstr_fd(strerror(errno), STDERR_FILENO); */
	ft_putstr_fd("\n", STDERR_FILENO);
	return(1);
	(void)exit_code;
}

void    ft_exit_clean(int exit_code, t_ms *ms)
{
	ft_clean_all(ms);
	exit(exit_code);
}
