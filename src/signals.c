/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:47:51 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/21 12:50:51 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t   g_signal;

static void ft_prompt_signal_handler(int signal_id)
{
    if (signal_id == SIGINT)
    {
        g_signal = SIGINT + 128;
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    ft_signals_interactive(void)
{
    //struct sigaction sa;

    // sa.sa_handler = ft_prompt_signal_handler;
    // sigemptyset(&sa.sa_mask);
    // sa.sa_flags = SA_RESTART;
    // sigaction(SIGINT, &sa, NULL);
    signal(SIGINT, ft_prompt_signal_handler);
    signal(SIGQUIT, SIG_IGN);
}

void    ft_signals_heredoc(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
}

void    ft_signals_default(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void    ft_signals_ignore(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
}
