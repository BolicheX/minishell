/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:47:51 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/21 17:56:28 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_prompt_signal_handler(int signal_id)
{
    if (signal_id == SIGINT)
    {
        g_signal = SIGINT;//Usar en builtin exit.
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

//Sets the behaviour of signals for minishell.
void    ft_signals_minishell()
{
    //struct sigaction sa;

    signal(SIGQUIT, SIG_IGN);
    // sa.sa_handler = ft_prompt_signal_handler;
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = SA_RESTART;
    // sigaction(SIGINT, &sa, NULL);
    signal(SIGINT, ft_prompt_signal_handler);
}

//Sets the behaviour of signals for a heredoc process.
void    ft_signals_heredoc()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_DFL);
}

//Sets the behaviour of signals for an execution process.
void    ft_signals_default()
{
    signal(SIGQUIT, SIG_DFL);
    signal(SIGINT, SIG_DFL);
}

//Prints a message or a newline if an unhandled signal terminated a process.
void    ft_print_signal_terminated(int status)
{
    int signal_id;

    if (WIFSIGNALED(status)) {
        signal_id = WTERMSIG(status);
        if (signal_id == SIGQUIT)//ctrl-\ en ejecución de programas debe funcionar.
            ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
        else if (signal_id == SIGINT)
            write(STDERR_FILENO, "\n", 1);
    }
}
