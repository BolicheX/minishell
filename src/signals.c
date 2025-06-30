/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:47:51 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/30 20:21:15 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_prompt_signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(STDERR_FILENO, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    // else if (sig == SIGQUIT)
    // {

    // }
}

//Restores the default behaviour of signals for a children process.
void    ft_restore_child_signals()
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

//Prints a message or a newline if an unhandled signal terminated a process.
void    ft_print_signal_terminated(int status)
{
    int signal;

    if (WIFSIGNALED(status)) {
        signal = WTERMSIG(status);
        if (signal == SIGQUIT)
            ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
        else if (signal == SIGINT)
            write(STDERR_FILENO, "\n", 1);
    }
}
