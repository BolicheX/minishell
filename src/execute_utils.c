/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 20:51:02 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/17 20:51:59 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_execute_if_is_builtin(t_cmd *cmd, int is_subshell, t_ms *ms)
{
    char    *cmd_name;
    int     exit_code;
    
    cmd_name = cmd->argv[0];
    exit_code = -1;
    if (ft_strcmp(cmd_name, "echo") == 0)
        exit_code = ft_echo(cmd);
    else if (ft_strcmp(cmd_name, "cd") == 0)
        exit_code = ft_cd(cmd, ms);
    else if (ft_strcmp(cmd_name, "pwd") == 0)
        exit_code = ft_pwd();
    else if (ft_strcmp(cmd_name, "export") == 0)
        exit_code = ft_export(cmd, ms);
    else if (ft_strcmp(cmd_name, "unset") == 0)
        exit_code = ft_unset(cmd, ms);
    else if (ft_strcmp(cmd_name, "env") == 0)
        exit_code = ft_env(ms);
    else if (ft_strcmp(cmd_name, "exit") == 0)
        exit_code = ft_exit(cmd, is_subshell, ms);
    return (exit_code);
}

//Returns the exit_code corresponding to an exit_status and prints accordingly.
int ft_get_exit_code(int exit_status)
{
    int exit_code;

    if (WIFEXITED(exit_status))
        return (WEXITSTATUS(exit_status));
    if (WIFSIGNALED(exit_status)) {
        exit_code = WTERMSIG(exit_status);
        if (exit_code == SIGQUIT)
            ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
        else if (exit_code == SIGINT)
            write(STDERR_FILENO, "\n", 1);//TODO Comprobar que hace falta y que debe ir por STDERR_FILENO.
        return (exit_code + 128);
    }
    return (-1);
}
