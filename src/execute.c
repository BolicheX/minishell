/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:23:45 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/16 16:45:36 by jescuder         ###   ########.fr       */
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

void    ft_execute_child(t_cmd *cmd, t_ms *ms)
{
    int     exit_code;
    char    **envp;

    ft_debug_print_msg(cmd->argv[0], "ft_execute_child: ");
    exit_code = ft_execute_if_is_builtin(cmd, 1, ms);
    if (exit_code != -1)
        ft_exit_clean(exit_code, ms);
    if (cmd->path == NULL)
        ft_exit_clean(127, ms);//Ya se mostró el mensaje de error en el parsing.
    envp = ft_env_to_array(ms);
    if (envp == NULL)
        ft_exit_perror(NULL, 1, ms);
    ft_signals_default();
    execve(cmd->path, cmd->argv, envp);
    if (errno == ENOENT)
        ft_exit_perror(cmd->path, 127, ms);//Comando no encontrado
    else if (errno == EACCES)
        ft_exit_perror(cmd->path, 126, ms);//Permiso denegado
    else
        ft_exit_perror(cmd->path, 1, ms);//Otro error
}

pid_t   ft_execute_fork(t_cmd *cmd, int input_fd, int output_fd, t_ms *ms)
{
    pid_t	child_process_id;

    if (input_fd == -1 || output_fd == -1)//TODO Probablemente gestionar todos los errores dentro del hijo para un correcto exit_code.
        return (-2);
    child_process_id = fork();
    if (child_process_id == -1)
        return (-1);
    else if (child_process_id == 0)
    {
        dup2(cmd->in, STDIN_FILENO);
        dup2(cmd->out, STDOUT_FILENO);
        ft_close_all(ms);
        ft_execute_child(cmd, ms);
    }
    return (child_process_id);
}

int ft_execute_one(t_cmd *cmd, t_ms *ms)
{
    pid_t   child_process_id;
    int     exit_code;
    int     exit_status;

    //ft_debug_print_str("ft_execute_one");
    exit_code = ft_execute_if_is_builtin(cmd, 0, ms);
    if (exit_code != -1)
        return (exit_code);
    child_process_id = ft_execute_fork(cmd, cmd->in, cmd->out, ms);
    if (child_process_id == -1)
        ft_exit_perror(NULL, 1, ms);
    if (child_process_id == -2)
        return (-1);
    ft_lstclear(&ms->cmds, ft_clean_cmd);
    waitpid(child_process_id, &exit_status, 0);
    return (ft_get_exit_code(exit_status));
}

int ft_execute_pipeline(t_list *cmds, int *child_ids, int cmds_count, t_ms *ms)
{
    int     i;
    t_cmd   *cmd;
    int     exit_status;

    //ft_debug_print_str("ft_execute_pipeline");
    i = 0;
    while (i < cmds_count)
    {
        cmd = (t_cmd *) cmds->content;
        child_ids[i] = ft_execute_fork(cmd, cmd->in, cmd->out, ms);
        if (child_ids[i] == -1)
            ft_exit_perror(NULL, 1, ms);
        cmds = cmds->next;
        i++;
    }
    ft_lstclear(&ms->cmds, ft_clean_cmd);
    i = 0;
    while (i < cmds_count)
    {
        if (child_ids[i] == -2)
            exit_status = 1;
        else
            waitpid(child_ids[i], &exit_status, 0);
        i++;
    }
    return (ft_get_exit_code(exit_status));
}

void    ft_execute(t_list *cmds, t_ms *ms)
{
    int exit_code;
    int cmds_count;
    int *child_ids;

    signal(SIGINT, SIG_IGN);
    if (cmds->next == NULL)
    {
        exit_code = ft_execute_one((t_cmd *) cmds->content, ms);
        if (exit_code != -1)
            g_signal = exit_code;
    }
    else
    {
        cmds_count = ft_lstsize(cmds);
        child_ids = malloc(sizeof(int) * cmds_count);//TODO pasar a ms para liberar en child.
        if (child_ids == NULL)
            ft_exit_perror(NULL, 1, ms);
        ms->child_ids = child_ids;
        exit_code = ft_execute_pipeline(cmds, child_ids, cmds_count, ms);
        if (exit_code != -1)
            g_signal = exit_code;
        free(child_ids);
        ms->child_ids = NULL;
    }
    ft_signals_minishell();
}
