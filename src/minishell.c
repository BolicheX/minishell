/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:43 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/27 17:49:16 by jescuder         ###   ########.fr       */
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

void	ft_execute_builtin(t_list *cmds, t_ms *ms)
{
	t_list	*current;
	char	**argv;

	current = cmds;
	while (current)
	{
		argv = ((t_cmd *)current->content)->argv;
		if (argv && argv[0] && ft_strcmp(argv[0], "echo") == 0)
			g_signal = ft_echo((t_cmd *)current->content);
		if (argv && argv[0] && ft_strcmp(argv[0], "pwd") == 0)
			g_signal = ft_pwd((t_cmd *)current->content);
		if (argv && argv[0] && ft_strcmp(argv[0], "cd") == 0)
			g_signal = ft_cd((t_cmd *)current->content, ms);
		if (argv && argv[0] && ft_strcmp(argv[0], "env") == 0)
			g_signal = ft_env((t_cmd *)current->content, ms);
		if (argv && argv[0] && ft_strcmp(argv[0], "export") == 0)
			g_signal = ft_export((t_cmd *)current->content, ms);
		if (argv && argv[0] && ft_strcmp(argv[0], "unset") == 0)
			g_signal = ft_unset((t_cmd *)current->content, ms);
		current = current->next;
	}
	//ft_lstclear(&ms->cmds, ft_clean_cmd);
}

//NOTA: Sustituye a ft_transform_cmd.
//Interprets a command line by lexing, expanding, parsing and executing.
//If it's a heredoc command, ft_heredoc manages the following lines, asks for
//more if necessary and sets the lines after the limiter to be traversed here
//after the execution of the heredoc command.
static int  ft_interpret_input_line(char *cmd_line, int i, t_ms *ms)
{
	int     is_heredoc;
	t_list  *tokens;
	t_list  *cmds;

    is_heredoc = 0;
    tokens = NULL;
	ft_lexing(cmd_line, &tokens);
	if(ft_heredoc_init(tokens, ms))
	{
		ft_lstclear(&tokens, ft_del_token);
		return (0);
	}
    if (ms->limiter != NULL)
    {
        is_heredoc = 1;
        if (ft_heredoc(i, ms) == 0)
            return (is_heredoc);
    }
    else
        ft_add_history(cmd_line, ms);
    if (ft_expand(tokens, ms) == -1)
		return (is_heredoc);
	//ft_lstiter(tokens, ft_print_token);//TODO Quitar tras confirmar debugging.
    // if (is_heredoc == 1)//Para pruebas
    //     ft_debug_print_fd(ms->heredoc[0], NULL, NULL);//Sustituye por la línea de abajo cuando quieras.
    // else
    // {
    //     ft_debug_print_msg("Execute:");
    //     ft_debug_print_msg(cmd_line);
    // }
    cmds = ft_parse(tokens, ms);
    ft_lstclear(&tokens, ft_del_token);
    ft_resolve_paths(cmds, ms);
    ft_print_cmd_list(cmds);//TODO Quitar tras confirmar debugging.
    ms->cmds = cmds;
    ft_execute(cmds, ms);
    ft_heredoc_close(ms);
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
        if (*input_lines[i] != '\0')//TODO Comprobar.
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
    char    *input;
    char    **input_lines;

    while (1)
    {
        input = readline("minishell$ ");
        if (input == NULL)
            ft_exit_error(NULL, NULL, "exit", 1, ms);
        //ft_debug_print_str(input, "-Input:", "-Fin Input.");
        input_lines = ft_split_empty(input, '\n');
        //ft_debug_print_array(input_lines, "-Input Line:", "-Fin Input Line.");
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

int main(int argc, char *argv[], char *envp[])
{
    t_ms    ms;

    ft_init(envp, &ms);
    if (argc != 1 || isatty(STDIN_FILENO) == 0)
        ft_non_interactive_mode(argc, argv, &ms);
    else
    {
        //ft_init_termios(&ms);//Conseguí gestionar señales como bash sin esto. Puede hacer falta más adelante.
        ft_setup_signals();
        ft_interactive_mode(&ms);
    }
    return (g_signal);
}
