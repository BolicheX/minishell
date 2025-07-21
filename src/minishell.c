/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:43 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/21 19:33:05 by jescuder         ###   ########.fr       */
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

void	ft_execute_builtin(t_ms *ms)
{
	t_list	*current;
	char	**argv;

	current = ms->cmds;
	while (current)
	{
		argv = ((t_cmd *)current->content)->argv;
		if (argv && argv[0] && ft_strcmp(argv[0], "echo") == 0)
			ms->status = ft_echo((t_cmd *)current->content);
		if (argv && argv[0] && ft_strcmp(argv[0], "pwd") == 0)
			ms->status = ft_pwd((t_cmd *)current->content);
		if (argv && argv[0] && ft_strcmp(argv[0], "cd") == 0)
			ms->status = ft_cd((t_cmd *)current->content, ms);
		if (argv && argv[0] && ft_strcmp(argv[0], "env") == 0)
			ms->status = ft_env((t_cmd *)current->content, ms);
		current = current->next;
	}
	ft_lstclear(&ms->cmds, ft_clean_cmd);
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
	ft_lexing(cmd_line, &tokens);//TODO JOSE Debe llamar a ft_heredoc_init si es un comando heredoc.
    if (ft_strcmp(cmd_line, "heredoc") == 0)//Para pruebas
        ft_heredoc_init("EOF", ms);
    if (ms->limiter != NULL)
    {
        is_heredoc = 1;
        if (ft_heredoc(i, ms) == 0)//Libera y setea ms->input_lines con las que siguen al limiter o con NULL si no hay.
            return (is_heredoc);
    }
    else
        ft_add_history(cmd_line, ms);
    ft_expand(tokens, ms);//TODO JOSE El limiter en un comando heredoc no debe expandirse. Puedes simplemente no expandir si ft_strcmp(str, limiter) == 0).
	//ft_lstiter(tokens, ft_print_token);//TODO Quitar tras confirmar debugging.
    ft_lstclear(&tokens, ft_del_token);
    // if (is_heredoc == 1)//Para pruebas
    //     ft_debug_print_fd(ms->heredoc[0], NULL, NULL);//Sustituye por la línea de abajo cuando quieras.
    // else
    // {
    //     ft_debug_print_msg("Execute:");
    //     ft_debug_print_msg(cmd_line);
    // }
    (void) cmds;
    // cmds = ft_parse(tokens);//TODO JOSE Debe asignar ms->heredoc[0] al campo "in" del t_cmd si es un comando heredoc.
    // ft_print_cmd_list(cmds);//TODO Quitar tras confirmar debugging.
    // ms->cmds = cmds;//TODO Probablemente no haga falta incluirlo en t_ms porque sólo hay que liberarlo en ft_execute_cmd_line.
    // ft_execute_cmd_line(cmds, ms);
    ft_heredoc_close(ms);//TODO Comprobar free a NULL.
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
            ft_exit_error("exit", 1, ms);
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
