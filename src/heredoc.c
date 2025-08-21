/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:01:14 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/22 00:14:32 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_child(char *history_entry, int fork_pipe[2], t_ms *ms)
{
	char	*input;

	ft_close(&fork_pipe[0]);
	if (ms->is_interactive == 0)
	{
		free(history_entry);
		ft_close(&fork_pipe[1]);
		ft_print_heredoc_error(ms);
		ft_exit_clean(2, ms);
	}
	ft_signals_heredoc();
	ft_add_history(history_entry, ms);
	free(history_entry);
	input = readline("> ");
	if (input == NULL)
	{
		ft_close(&fork_pipe[1]);
		ft_print_heredoc_error(ms);
		ft_exit_clean(2, ms);
	}
	ft_putstr_fd(input, fork_pipe[1]);
	ft_close(&fork_pipe[1]);
	ft_exit_clean(0, ms);
}

static pid_t	ft_heredoc_fork(char *history_entry, int fork_pipe[2], t_ms *ms)
{
	pid_t	child_id;

	if (pipe(fork_pipe) == -1)
	{
		free(history_entry);
		ft_exit_perror(NULL, 1, ms);
	}
	child_id = fork();
	if (child_id == -1)
	{
		free(history_entry);
		ft_close(&fork_pipe[0]);
		ft_close(&fork_pipe[1]);
		ft_exit_perror(NULL, 1, ms);
	}
	else if (child_id == 0)
		ft_heredoc_child(history_entry, fork_pipe, ms);
	ft_close(&fork_pipe[1]);
	return (child_id);
}

//Calls readline in a child process to achieve correct SIGINT handling and
//independent history behaviour, sets ms->input_lines to the result.
static int	ft_heredoc_readline(char *history_entry, t_ms *ms)
{
	int		fork_pipe[2];
	pid_t	child_id;
	int		exit_status;
	char	*input;

	ft_signals_ignore();
	child_id = ft_heredoc_fork(history_entry, fork_pipe, ms);
	waitpid(child_id, &exit_status, 0);
	input = ft_fd_to_str(fork_pipe[0]);
	ft_close(&fork_pipe[0]);
	if (input == NULL)
	{
		free(history_entry);
		ft_exit_perror(NULL, 1, ms);
	}
	if (ft_update_input_lines(input, ms) == 0)
	{
		free(history_entry);
		ft_exit_perror(NULL, 1, ms);
	}
	return (ft_get_exit_code_heredoc(exit_status, ms));
}

//Writes in the heredoc pipe, manages the heredoc history entry, indicates if
//more heredoc input is required and updates ms->input_lines after the limiter.
static int	ft_heredoc_traverse_input(int i, char **history_entry_p, t_ms *ms)
{
	char	**input_lines;

	input_lines = ms->input_lines;
	if (input_lines[i] != NULL && ft_strchr(*history_entry_p, '\n') == NULL)
		ft_update_history_entry(history_entry_p, NULL, ms);
	while (input_lines[i] != NULL)
	{
		ft_update_history_entry(history_entry_p, input_lines[i], ms);
		if (ft_strcmp(input_lines[i], ms->limiter) == 0)
		{
			ft_add_history(*history_entry_p, ms);
			free(*history_entry_p);
			ft_trim_input_lines(++i, ms);
			ft_close(&ms->heredoc[1]);
			return (1);
		}
		else if (ft_heredoc_write(input_lines[i], ms) == 0)
		{
			free(*history_entry_p);
			ft_exit_perror(NULL, 1, ms);
		}
		i++;
	}
	return (0);
}

//Writes in the heredoc pipe, manages the heredoc history entry, asks for more
//heredoc input while it's required, updates ms->input_lines after the limiter
//is found and indicates if the execution must be canceled because of a SIGINT.
int	ft_heredoc(int i, t_ms *ms)
{
	char	*history_entry;
	int		exit_code;

	history_entry = ft_strdup(ms->input_lines[i]);
	if (history_entry == NULL)
		ft_exit_perror(NULL, 1, ms);
	i++;
	while (1)
	{
		if (ft_heredoc_traverse_input(i, &history_entry, ms) == 1)
			return (1);
		exit_code = ft_heredoc_readline(history_entry, ms);
		if (exit_code != 0)
		{
			ft_close(&ms->heredoc[1]);
			ft_add_history(history_entry, ms);
			free(history_entry);
			if (exit_code == -1)
				return (0);
			else
				return (1);
		}
		i = 0;
	}
}
