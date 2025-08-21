/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:30:13 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 13:20:37 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_handle_heredoc_token(t_list *tokens, t_ms *ms)
{
	t_token	*tok;
	t_list	*next;

	next = tokens->next;
	if (!next)
		return (ft_error("syntax error near unexpected token", NULL, "`newline'", ms));
	tok = (t_token *)next->content;
	if (tok->type != T_WORD)
		return (ft_error("syntax error near unexpected token", NULL, tok->value, ms));
	ms->limiter = ft_strdup(tok->value);
	if (!ms->limiter)
		ft_exit_perror(NULL, 1, ms);
	if (pipe(ms->heredoc) == -1)
		ft_exit_perror(NULL, 1, ms);
	return(0);
}

int	ft_heredoc_init(t_list *tokens, t_ms *ms)
{
	t_token	*tok;

    free(ms->limiter);
	ms->limiter = NULL;
    ft_close(&ms->heredoc[0]);
	ft_close(&ms->heredoc[1]);
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type == T_REDIR && ft_strcmp(tok->value, "<<") == 0)
			return (ft_handle_heredoc_token(tokens, ms));
		tokens = tokens->next;
	}
	return (0);
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

//Prints a warning when EOF(ctrl-D) is used as heredoc input.
void    ft_print_heredoc_error(t_ms *ms)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    if (ms->is_interactive == 0)
	{
		ft_putstr_fd("line ", STDERR_FILENO);
		ft_putnbr_fd(ms->lines_count, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
    ft_putstr_fd("warning: here-document at line ", STDERR_FILENO);
    ft_putnbr_fd(ms->lines_count, STDERR_FILENO);
    ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
    ft_putstr_fd(ms->limiter, STDERR_FILENO);
    ft_putendl_fd("')", STDERR_FILENO);
}

int ft_get_exit_code_heredoc(int exit_status, t_ms *ms)
{
    if (WIFEXITED(exit_status))
    {
        ms->exit_code = 0;
        return (WEXITSTATUS(exit_status));
    }
    write(STDOUT_FILENO, "\n", 1);
    ms->exit_code = SIGINT + 128;
    return (-1);
}
