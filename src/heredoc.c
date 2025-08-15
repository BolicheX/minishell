/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 10:01:14 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/15 19:30:49 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_heredoc_child(char *history_entry, int fork_pipe[2], t_ms *ms)
{
    char    *input;

    ft_close(&fork_pipe[0]);
    ft_signals_heredoc();
    ft_add_history(history_entry, ms);
    free(history_entry);
    input = readline("> ");
    if (input == NULL)
    {
        ft_close(&fork_pipe[1]);
        ft_print_heredoc_error(ms);
        //ft_debug_print_str("Child End");
        ft_exit_clean(2, ms);
    }
    ft_putstr_fd(input, fork_pipe[1]);
    ft_close(&fork_pipe[1]);
    //ft_debug_print_str("Child End");
    ft_exit_clean(0, ms);
}

static pid_t    ft_heredoc_fork(char *history_entry, int fork_pipe[2], t_ms *ms)
{
    pid_t   child_process_id;

    if (pipe(fork_pipe) == -1)
    {
        free(history_entry);
        ft_exit_perror(NULL, 1, ms);
    }
    child_process_id = fork();
    if (child_process_id == -1)
    {
        free(history_entry);
        ft_close(&fork_pipe[0]);
        ft_close(&fork_pipe[1]);
        ft_exit_perror(NULL, 1, ms);
    }
    else if (child_process_id == 0)
        ft_heredoc_child(history_entry, fork_pipe, ms);
    ft_close(&fork_pipe[1]);
    return (child_process_id);
}

//Calls readline in a child process to achieve correct SIGINT handling and
//independent history behaviour, sets ms->input_lines to the result.
static int  ft_heredoc_readline(char *history_entry, t_ms *ms)
{
    int     fork_pipe[2];
    pid_t   child_process_id;
    int     exit_status;
    char    *input;

    signal(SIGINT, SIG_IGN);
    child_process_id = ft_heredoc_fork(history_entry, fork_pipe, ms);
    waitpid(child_process_id, &exit_status, 0);
    ft_signals_minishell();
    input = ft_fd_to_str(fork_pipe[0]);
    ft_close(&fork_pipe[0]);
    if (input == NULL)
    {
        free(history_entry);
        ft_exit_perror(NULL, 1, ms);
    }
    //ft_debug_print_lines(input, "-Heredoc Input:", "-Fin Heredoc Input.");
    ft_update_input_lines(ft_split_empty(input, '\n'), ms);
    if (WIFEXITED(exit_status))
        return (WEXITSTATUS(exit_status));
    write(STDOUT_FILENO, "\n", 1);
    return (-1);
}

static int	ft_heredoc_write(char *input_line, t_ms *ms)
{
	char	*expanded_line;

	expanded_line = ft_strdup(input_line);
	if (!expanded_line)
		return (0);
	if (!ft_check_expand(&expanded_line, ms))
	{
		free(expanded_line);
		return (0);
	}
	ft_putendl_fd(expanded_line, ms->heredoc[1]);
	free(expanded_line);
	return (1);
}

//Writes in the heredoc pipe, manages the heredoc history entry, indicates if
//more heredoc input is required and updates ms->input_lines after the limiter.
static int  ft_heredoc_traverse_input(int i, char **history_entry_p, t_ms *ms)
{
    char    **input_lines;

    input_lines = ms->input_lines;
    if (input_lines[i] != NULL && ft_strchr(*history_entry_p, '\n') == NULL)
    {
        //ft_debug_print_str("Primer salto de línea.");
        ft_update_history_entry(history_entry_p, NULL, ms);
    }
    while (input_lines[i] != NULL)
    {
        //ft_debug_print_lines(input_lines[i], "-Heredoc Traverse line:", "-Fin Heredoc Traverse line.");
        ft_update_history_entry(history_entry_p, input_lines[i], ms);
        if (ft_strcmp(input_lines[i], ms->limiter) == 0)
        {
            ft_add_history(*history_entry_p, ms);
            free(*history_entry_p);
            ft_trim_input_lines(++i, ms);
            //ft_debug_print_str("-Heredoc Traverse limiter");
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
    //ft_debug_print_str("-Heredoc Traverse NO limiter");
    return (0);
}

//Writes in the heredoc pipe, manages the heredoc history entry, asks for more
//heredoc input while it's required, updates ms->input_lines after the limiter
//is found and indicates if the execution must be canceled because of a SIGINT.
int ft_heredoc(int i, t_ms *ms)
{
    char    *history_entry;
    int     exit_code;

    //ft_debug_print_str("-Heredoc Function");
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
            //ft_debug_print_str("-Heredoc Function End exit_code != 0");
            ft_close(&ms->heredoc[1]);
            ft_add_history(history_entry, ms);
            free(history_entry);
            if (exit_code == -1)//SIGINT
                return (0);//Cancelar la ejecución del comando heredoc.
            else
                return (1);//Terminar bucle y ejecutar el comando heredoc.
        }
        i = 0;
    }
}
