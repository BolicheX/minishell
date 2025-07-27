/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescuder <jescuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:02:24 by jescuder          #+#    #+#             */
/*   Updated: 2025/07/26 13:27:49 by jescuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Closes a fd in a secure way checking and setting a -1 value.
void	ft_close(int *fd)
{
	if (*fd == -1)
        return ;
	if (close(*fd) == -1)
        ft_perror("error");
    *fd = -1;
}

//Closes every file descriptor in t_ms.
static void	ft_close_all(t_ms *ms)
{
	ft_close(&ms->heredoc[0]);
	ft_close(&ms->heredoc[1]);
}

//La dejo por si por algun motivo se necesita cerrar los fds de los comandos sin liberar la memoria de los comandos.
//Pero por ahora se usa ft_clean_cm tanto para liberar memoria como para cerrar los fds.
/* static void	ft_close_cmd(t_ms *ms)
{
	t_list	*cmd_list;
	t_cmd	*cmd;

	if (!ms || !ms->cmds)
		return;
	cmd_list = ms->cmds;
	while (cmd_list)
	{
		cmd = (t_cmd *)cmd_list->content;
		if (cmd)
		{
			if (cmd->in != STDIN_FILENO && cmd->in >= 0)
			{
				close(cmd->in);
				cmd->in = -1;
			}
			if (cmd->out != STDOUT_FILENO && cmd->out >= 0)
			{
				close(cmd->out);
				cmd->out = -1;
			}
		}
		cmd_list = cmd_list->next;
	}
} */

void	ft_clean_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (!cmd)
		return;
	if (cmd->in != STDIN_FILENO)
		ft_close(&cmd->in);
	if (cmd->out != STDOUT_FILENO)
		ft_close(&cmd->out);
	ft_free_str_array(cmd->argv);
	free(cmd->path);
	free(cmd);
}

void	ft_clean_parse(t_list *cmd_list, t_cmd *cmd)
{
	if (cmd_list)
	{
		ft_lstclear(&cmd_list, ft_clean_cmd);
		cmd_list = NULL;
	}
	if (cmd)
		ft_clean_cmd(cmd);
}

//Frees all heap memory in t_ms.
static void ft_free_all(t_ms *ms)
{
	//ft_free_str_array(ms->envp);
	//ft_free_str_array(ms->envp_paths);
	ft_kvl_clear(&ms->env, free);
    free(ms->last_history_entry);
    ft_free_str_array(ms->input_lines);
    free(ms->limiter);
	ft_lstclear(&ms->cmds, ft_clean_cmd);

	//TODO Los demás campos de ms que estén en heap memory.
}

//Closes every file descriptor and frees all heap memory in t_ms,
//and restores the original terminal configuration.
void    ft_clean_all(t_ms *ms)
{
    ft_close_all(ms);
    ft_free_all(ms);
	//ft_restore_terminal(ms);
}
