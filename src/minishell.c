/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:43 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/03 22:37:42 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		current = current->next;
	}
	ft_lstclear(&ms->cmds, ft_clean_cmd);
}

static void ft_interactive_mode(t_ms *ms)
{
    char    *cmd_line;

    while (1)
    {
        cmd_line = readline("minishell$ ");
        if (cmd_line == NULL)
            ft_exit_error("exit", 1, ms);
        if (*cmd_line != '\0')
            add_history(cmd_line);
        if (ft_strcmp(cmd_line, "exit") == 0)
        {
            free(cmd_line);
            ft_exit_error("exit", 1, ms);
        }
        //printf("%s\n", cmd_line);
        ft_transform_cmd(cmd_line, ms);
		ft_execute_builtin(ms);
        //ft_execute_cmd(&ms);
        ms->cmd_lines_num++;
        free(cmd_line);
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
    return (0);
}
