/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:30:13 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/19 12:41:29 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_heredoc_init(char *limiter, t_ms *ms)
{
    ms->limiter = ft_strdup(limiter);
    if (pipe(ms->heredoc) == -1)
        ft_exit_perror(NULL, 1, ms);
}

void    ft_heredoc_close(t_ms *ms)
{
    free(ms->limiter);
    ms->limiter = NULL;
    ft_close(&ms->heredoc[0]);
	ft_close(&ms->heredoc[1]);
}

void    ft_update_history_entry(char **history_entry_p, char *line, t_ms *ms)
{
    char    *temp;

    if (line != NULL)
    {
        temp = *history_entry_p;
        *history_entry_p = ft_strjoin(temp, line);
        free(temp);
        if (*history_entry_p == NULL)
            ft_exit_perror(NULL, 1, ms);
    }
    temp = *history_entry_p;
    *history_entry_p = ft_strjoin(temp, "\n");
    free(temp);
    if (*history_entry_p == NULL)
        ft_exit_perror(NULL, 1, ms);
}

void    ft_trim_input_lines(int start, t_ms *ms)
{
    char    **temp;

    temp = ms->input_lines;
    ms->input_lines = ft_str_subarray(temp, start, ft_str_arraylen(temp));
    ft_free_str_array(temp);
    if (ms->input_lines == NULL)
        ft_exit_perror(NULL, 1, ms);
}

//Prints a warning when EOF(ctrl-D) is used as heredoc input.
void    ft_print_heredoc_error(t_ms *ms)
{
    ft_putstr_fd("-minishell: warning: here-document at line ", STDERR_FILENO);
    ft_putnbr_fd(ms->cmd_prompts_count, STDERR_FILENO);
    ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
    ft_putstr_fd(ms->limiter, STDERR_FILENO);
    ft_putendl_fd("')", STDERR_FILENO);
}
