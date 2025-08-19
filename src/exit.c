/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:43:56 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/19 17:52:15 by jose-jim         ###   ########.fr       */
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
	g_signal = exit_code;
	return(exit_code);
}

int	ft_syntax_error(char *token, int exit_code)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	g_signal = exit_code;
	return (exit_code);
}

void    ft_exit_clean(int exit_code, t_ms *ms)
{
	ft_clean_all(ms);
	exit(exit_code);
}
