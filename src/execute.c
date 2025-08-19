/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:23:45 by jescuder          #+#    #+#             */
/*   Updated: 2025/08/19 17:55:55 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_execute_child(t_cmd *cmd, t_ms *ms)
{
    int     exit_code;
    char    **envp;

    //ft_debug_print_msg(cmd->argv[0], "ft_execute_child: ");//TODO QUITAR cuando acabemos.
    exit_code = ft_execute_if_is_builtin(cmd, 1, ms);
    if (exit_code != -1)
        ft_exit_clean(exit_code, ms);
    if (cmd->path == NULL)
	{
		ft_error(cmd->argv[0], NULL, "command not found", 127);
		ft_exit_clean(127, ms);
	}
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
    pid_t	child_id;

    if (input_fd == -1 || output_fd == -1)//TODO Probablemente gestionar todos los errores dentro del hijo para un correcto exit_code.
        return (-1);
    child_id = fork();
    if (child_id == -1)
        return (-2);
    else if (child_id == 0)
    {
        dup2(cmd->in, STDIN_FILENO);
        dup2(cmd->out, STDOUT_FILENO);
        ft_close_all(ms);
        ft_execute_child(cmd, ms);
    }
    return (child_id);
}

int ft_execute_one(t_cmd *cmd, t_ms *ms)
{
    pid_t   child_id;
    int     exit_code;
    int     exit_status;

    exit_code = ft_execute_if_is_builtin(cmd, 0, ms);
    if (exit_code != -1)
        return (exit_code);
    child_id = ft_execute_fork(cmd, cmd->in, cmd->out, ms);
    if (child_id == -2)
        ft_exit_perror(NULL, 1, ms);
    if (child_id == -1)
        return (-1);
    ft_lstclear(&ms->cmds, ft_clean_cmd);
    waitpid(child_id, &exit_status, 0);
    return (ft_get_exit_code(exit_status));
}

int ft_execute_pipeline(t_list *cmds, int *child_ids, int cmds_count, t_ms *ms)
{
    int     i;
    t_cmd   *cmd;
    int     exit_status;

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

    ft_signals_ignore();
    if (cmds->next == NULL)
    {
        exit_code = ft_execute_one((t_cmd *) cmds->content, ms);
        if (exit_code != -1)
            g_signal = exit_code;
    }
    else
    {
        cmds_count = ft_lstsize(cmds);
        child_ids = malloc(sizeof(int) * cmds_count);
        if (child_ids == NULL)
            ft_exit_perror(NULL, 1, ms);
        ms->child_ids = child_ids;
        exit_code = ft_execute_pipeline(cmds, child_ids, cmds_count, ms);
        if (exit_code != -1)
            g_signal = exit_code;
        free(child_ids);
        ms->child_ids = NULL;
    }
}
