/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:43 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/15 17:35:48 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t   g_signal;

//If there are arguments or STDIN_FILENO was redirected to a file or a pipe,
//we execute in a non-interactive mode.
static void ft_non_interactive_mode(int argc, char *argv[], t_ms *ms)
{
	(void) argc;
	(void) argv;
	ft_exit_clean(1, ms);
}

//Interprets a command line by lexing, expanding, parsing and executing.
//If it's a heredoc command, ft_heredoc manages the following lines, asks for
//more if necessary and sets the lines after the limiter to be traversed here
//after the execution of the heredoc command.
static int  ft_interpret_input_line(char *cmd_line, int i, t_ms *ms)
{
	int     is_heredoc;

    is_heredoc = 0;
	if (ft_lexing(cmd_line, &ms->tokens))
		return (0);
	if(ft_heredoc_init(ms->tokens, ms))
		return (0);
    if (ms->limiter != NULL)
    {
        is_heredoc = 1;
        if (ft_heredoc(i, ms) == 0)
            return (is_heredoc);
    }
    else
        ft_add_history(cmd_line, ms);
    if (ft_expand(ms) == -1)
		return (is_heredoc);
	ft_lstclear(&ms->cmds, ft_clean_cmd);
    ft_parse(ms);
	if (!ms->cmds)
		return (is_heredoc);
    if (ft_resolve_paths(ms->cmds, ms))
		return (is_heredoc);
    //ft_print_cmd_list(cmds);//TODO Quitar tras confirmar debugging.
    ft_execute(ms->cmds, ms);
    return (is_heredoc);
}

//Traverses input lines to interpret them. It returns if a heredoc is
//found, because the following input lines are managed internally
//since more can be added in the heredoc input.
static void ft_traverse_input(t_ms *ms)
{
    char    **input_lines;
    int     i;
    int     is_heredoc;

    input_lines = ms->input_lines;
    if (input_lines == NULL)
        return ;
    i = 0;
    while (input_lines[i] != NULL)
    {
        if (*input_lines[i] != '\0')
        {
            is_heredoc = ft_interpret_input_line(input_lines[i], i, ms);
            if (is_heredoc == 1)
            {
                ft_traverse_input(ms);
                return ;
            }
        }
        i++;
    }
}

static void ft_interactive_mode(t_ms *ms)
{
    char    *prompt;
    char    *input;
    char    **input_lines;

    prompt = "\001\033[1;34m\002minishell\001\033[0m\002$ ";
    while (1)
    {
        input = readline(prompt);
        if (input == NULL)
        {
            ft_putendl_fd("exit", STDERR_FILENO);
            ft_exit_clean(g_signal, ms);
        }
        //ft_debug_print_lines(input, "-Input:", "-Fin Input.");
        input_lines = ft_split_empty(input, '\n');
        //ft_debug_print_array(input_lines, "-Input lines:", "-Fin Input lines.");
        free(input);
        if (input_lines == NULL)
            ft_exit_perror(NULL, 1, ms);
        ms->input_lines = input_lines;
        ft_traverse_input(ms);
        ft_free_str_array(ms->input_lines);
        ms->input_lines = NULL;
        ms->cmd_prompts_count++;
    }
}

/* int ft_launch_minishell(char *input, t_ms *ms)
{
    char    **commands;
    int     i;
    int     is_heredoc;
    int     last_exit_code = 0;

    // Divide la línea completa en comandos separados por ';'
    commands = ft_split(input, ';');
    if (!commands)
        ft_exit_perror("malloc", 1, ms);
    for (i = 0; commands[i] != NULL; i++)
    {
        if (*commands[i] == '\0')
            continue; // Ignorar comandos vacíos
        is_heredoc = ft_interpret_input_line(commands[i], i, ms);
        if (is_heredoc)
            break;
        last_exit_code = g_signal;
    }

    ft_free_str_array(commands);
    return last_exit_code;
} */

int main(int argc, char *argv[], char *envp[])
{
    t_ms ms;

    ft_init(envp, &ms);

/*     if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
    {
        // Ejecuta el minishell con el comando dado en argv[2]
        int exit_status = ft_launch_minishell(argv[2], &ms);
        ft_exit_clean(exit_status, &ms);
    } */
    if (argc != 1 || isatty(STDIN_FILENO) == 0)
        ft_non_interactive_mode(argc, argv, &ms);
    else
    {
        ft_setup_signals();
        ft_interactive_mode(&ms);
    }
    return (g_signal);
}
