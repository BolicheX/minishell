/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:43:56 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 22:01:08 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror(char *perror_prefix, t_ms *ms)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (ms->is_interactive == 0)
	{
		ft_putstr_fd("line ", STDERR_FILENO);
		ft_putnbr_fd(ms->lines_count, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (perror_prefix != NULL)
		perror(perror_prefix);
	else
		perror("error");
}

void	ft_exit_perror(char *perror_prefix, int exit_code, t_ms *ms)
{
	ft_perror(perror_prefix, ms);
	ft_exit_clean(exit_code, ms);
}

int	ft_error(char *cmd, char *arg, char *msg, t_ms *ms)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (ms->is_interactive == 0)
	{
		ft_putstr_fd("line ", STDERR_FILENO);
		ft_putnbr_fd(ms->lines_count, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
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
	ft_putstr_fd("\n", STDERR_FILENO);
	ms->exit_code = 1;
	return (1);
}

int	ft_syntax_error(char *token, int exit_code, t_ms *ms)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	ms->exit_code = exit_code;
	return (exit_code);
}

void	ft_exit_clean(int exit_code, t_ms *ms)
{
	ft_clean_all(ms);
	exit(exit_code);
}
