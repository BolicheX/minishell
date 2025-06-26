/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:41:43 by jescuder          #+#    #+#             */
/*   Updated: 2025/06/26 18:03:09 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//There are arguments or STDIN_FILENO was redirected to a file or a pipe,
//so we don't execute in interactive mode.
void    ft_non_interactive_execution(int argc, char *argv[], t_ms *ms)
{
    (void) argc;
    (void) argv;
    ft_exit_clean(1, ms);
}

int main(int argc, char *argv[], char *envp[])
{
    t_ms    ms;
    char    *cmd_line;

    ft_init(envp, &ms);
    if (argc != 1 || isatty(STDIN_FILENO) == 0)
        ft_non_interactive_execution(argc, argv, &ms);
    while (1)
    {
        //TODO Probablemente haya que actualizar envp en cada iteración, por si cambia. Probablemente con getenv.
        cmd_line = readline("$ ");
        if (cmd_line == NULL)
        {
            ft_putendl_fd("exit", STDERR_FILENO);
            return (1);
        }
        //printf("%s\n", cmd_line);
        ft_transform_cmd(cmd_line, &ms); //Lexing+Expanding+Parsing. Cámbiale el nombre a esta función a tu gusto.
        //ft_execute_cmd(&ms);
        ms.cmd_lines_num++;
        free(cmd_line);
    }
    return (0);
}
